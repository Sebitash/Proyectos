package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"os"

	"strings"

	"github.com/docker/docker/api/types/container"
	"github.com/docker/docker/api/types/image"
	"github.com/docker/docker/client"
	"github.com/docker/go-connections/nat"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

const uri = "mongodb://localhost:27017"

func StartMongoDbContainer() error {
	cli, err := client.NewClientWithOpts(client.FromEnv, client.WithAPIVersionNegotiation())
	if err != nil {
		log.Fatalf("Failed to create docker client: %v", err)
		return err
	}
	mongoImage := "mongodb/mongodb-community-server:7.0.11-rc2-ubi8"
	ctx := context.Background()
	config := container.Config{
		Image:        mongoImage,
		ExposedPorts: nat.PortSet{"27017": struct{}{}},
	}
	hostConfig := container.HostConfig{
		PortBindings: map[nat.Port][]nat.PortBinding{nat.Port("27017"): {{HostIP: "127.0.0.1", HostPort: "27017"}}},
	}
	out, err := cli.ImagePull(ctx, mongoImage, image.PullOptions{})
	defer out.Close()
	if err != nil {
		log.Fatalf("Error pulling image: %v", err)
		return err
	}

	_, err = io.Copy(os.Stdout, out)
	if err != nil {
		log.Fatalf("Error reading image pull output: %v", err)
		return err
	}

	fmt.Println("\nImage pulled successfully.")

	containers, err := cli.ContainerList(ctx, container.ListOptions{All: true})
	if err != nil {
		fmt.Println("Failed to get container list")
		return err
	}
	containerName := "historia-clinica-db"
	startOptions := container.StartOptions{}
	for _, container := range containers {
		if !strings.Contains(container.Names[0], containerName) {
			continue
		}
		state := container.State
		if state == "running" {
			fmt.Println("The container is already running. Doing nothing.")
		} else {
			fmt.Println("The container exists but is stopped. Starting container.")
			cli.ContainerStart(ctx, container.ID, startOptions)
		}
		return nil
	}
	fmt.Println("The container does not exist. Creating container.")
	resp, err := cli.ContainerCreate(ctx, &config, &hostConfig, nil, nil, containerName)
	if err != nil {
		fmt.Println("Failed to create container")
		return err
	}

	if err := cli.ContainerStart(ctx, resp.ID, container.StartOptions{}); err != nil {
		fmt.Println("Failed to start container")
		return err
	}
	fmt.Println("Container started successfully")
	return nil
}

func createMongoClient() (*mongo.Client, error) {
	serverAPI := options.ServerAPI(options.ServerAPIVersion1)
	opts := options.Client().ApplyURI(uri).SetServerAPIOptions(serverAPI)
	// Create a new client and connect to the server
	client, err := mongo.Connect(context.TODO(), opts)
	if err != nil {
		log.Fatalf("Failed to connect to mongodb: %v", err)
		return nil, err
	}
	// Send a ping to confirm a successful connection
	var result bson.M
	if err := client.Database("db").RunCommand(context.TODO(), bson.D{{"ping", 1}}).Decode(&result); err != nil {
		log.Fatalf("Failed to ping database: %v", err)
		return nil, err
	}
	log.Println("Mongodb client created successfully")
	return client, nil
}
