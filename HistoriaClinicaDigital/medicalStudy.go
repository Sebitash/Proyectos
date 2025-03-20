package main

import (
	"context"
	"fmt"
	"io"
	"log"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
)

type File struct {
	ID          string `bson:"_id,omitempty"`
	UserID      string `bson:"user_id"`
	Date        string `bson:"date"`
	Filename    string `bson:"filename"`
	Name        string `bson:"name"`
	Type        string `bson:"type"`
	Description string `bson:"description"`
	Data        []byte `bson:"data"`
}

func saveOrUpdateFile(client *mongo.Client, c *gin.Context, file File) {
	filesDb := client.Database("db").Collection("files")
	_, err := filesDb.InsertOne(c, file)
	if err != nil {
		filter := bson.D{{"_id", file.ID}}
		update := bson.D{{"$set", bson.D{
			{"data", file.Data},
			{"name", file.Name},
			{"type", file.Type},
			{"description", file.Description},
			{"date", file.Date},
		}}}
		_, err := filesDb.UpdateOne(c, filter, update)
		if err != nil {
			panic("Error inserting file into MongoDB")
		}
	}
}

func getFileInfo(c *gin.Context) ([]byte, string) {
	file, err := c.FormFile("file")
	if err != nil {
		panic("missing file in request")
	}

	fileData, err := file.Open()
	if err != nil {
		panic("error opening file")
	}
	defer fileData.Close()

	data, err := io.ReadAll(fileData)
	if err != nil {
		panic("error reading file")
	}
	return data, file.Filename
}

func getHexUserId(client *mongo.Client, c *gin.Context) string {
	hexUserId, err := c.Cookie("user_id")
	fmt.Println("hexUserId = %s", hexUserId)
	if err != nil {
		//panic("user_id not found")
		hexUserId = "67261f5ba87de2f23c16765a"
	}

	primitiveUserID, err := primitive.ObjectIDFromHex(hexUserId)
	if err != nil {
		panic("error decoding hex user_id")
	}
	coll := client.Database("db").Collection("accounts")
	filter := bson.D{{"_id", primitiveUserID}}
	result := Account{}
	err = coll.FindOne(context.TODO(), filter).Decode(&result)
	if err != nil {
		panic("user not found")
	}
	return hexUserId
}

func saveMedicalStudy(client *mongo.Client, c *gin.Context) {
	userId := getHexUserId(client, c)

	data, filename := getFileInfo(c)

	newFile := createNewFile(userId, filename, c, data)
	saveOrUpdateFile(client, c, newFile)
	newFile.Data = nil
}

func deleteMedicalStudy(client *mongo.Client, c *gin.Context) {
	file := getMedicalStudy(client, c)
	filesDb := client.Database("db").Collection("files")
	filter := bson.D{{"_id", file.ID}}
	_, err := filesDb.DeleteOne(c, filter)
	if err != nil {
		panic("Error deleting file")
	}
}

func updateMedicalStudy(client *mongo.Client, c *gin.Context) {
	file := getMedicalStudy(client, c)
	filesDb := client.Database("db").Collection("files")
	filter := bson.D{{"_id", file.ID}}
	update := bson.D{{"$set", bson.D{
		{"name", c.PostForm("name")},
		{"type", c.PostForm("type")},
		{"description", c.PostForm("description")},
		{"date", c.PostForm("date")},
	}}}
	_, err := filesDb.UpdateOne(c, filter, update)
	if err != nil {
		log.Println("pjjjjjjjj")
		panic("Error inserting file into MongoDB")
	}
}

func createNewFile(userId string, filename string, c *gin.Context, data []byte) File {
	id := userId + "_" + filename
	parsedDate, _ := time.Parse("2006-01-02", c.PostForm("date"))
	newFile := File{
		ID:          id,
		UserID:      userId,
		Filename:    filename,
		Data:        data,
		Name:        c.PostForm("name"),
		Type:        c.PostForm("type"),
		Description: c.PostForm("description"),
		Date:        parsedDate.Format("2006-01-02"),
	}
	return newFile
}

// returns a single user's study file
func getMedicalStudyFile(client *mongo.Client, c *gin.Context) {
	file := getMedicalStudy(client, c)

	c.Header("Content-Disposition", "attachment; filename="+file.Filename)
	c.Header("Content-Type", "application/octet-stream")
	c.Data(http.StatusOK, "application/octet-stream", file.Data)
}

// returns a single user's study data
func getMedicalStudyData(client *mongo.Client, c *gin.Context) File {
	file := getMedicalStudy(client, c)
	file.Data = nil
	return file
}

// returns all user's studies data
func getUserMedicalStudiesData(client *mongo.Client, c *gin.Context) []File {
	userId := getHexUserId(client, c)

	filesDb := client.Database("db").Collection("files")
	cursor, err := filesDb.Find(context.TODO(), bson.D{
		{"user_id", userId},
	})
	if err != nil {
		if err == mongo.ErrNoDocuments {
			panic("file not found")
		}
		panic("error obtaining file from db")
	}

	defer cursor.Close(context.TODO())

	var files []File
	for cursor.Next(context.TODO()) {
		var file File
		if err := cursor.Decode(&file); err != nil {
			panic("Error decoding file")
		}
		file.Data = nil
		files = append(files, file)
	}

	return files
}

func getMedicalStudy(client *mongo.Client, c *gin.Context) File {
	userId := getHexUserId(client, c)

	filename := c.Query("filename")
	if filename == "" {
		fmt.Println("no lo obtuve")
		filename = c.PostForm("filename")
	}
	fmt.Println("obtaining filename: ", filename)

	filesDb := client.Database("db").Collection("files")
	file := File{}
	id := userId + "_" + filename
	fmt.Println("Getting file with ID: " + id + " and user_id: " + userId)
	err := filesDb.FindOne(context.TODO(), bson.D{
		{"_id", id},
		{"user_id", userId},
	}).Decode(&file)
	if err != nil {
		panic("file not found")
	}
	return file
}
