package main

import (
	"fmt"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
)

type Recipe struct {
	ID          string `bson:"_id,omitempty"`
	UserID      string `bson:"user_id"`
	Data        []byte `bson:"data"`
	Filename    string `bson:"filename"`
	Name        string `bson:"name"`
	Description string `bson:"description"`
	Field       string `bson:"field"`
	Date        string `bson:"date"`
}

func insertRecipe(mongoClient *mongo.Client, c *gin.Context) {
	userId := getHexUserId(mongoClient, c)
	fileData, fileName := getFileInfo(c)

	recipe := createRecipe(c, userId, fileData, fileName)

	saveRecipeIntoDB(mongoClient, c, recipe)
}

func updateRecipe(mongoClient *mongo.Client, c *gin.Context) {
	recipesDB := mongoClient.Database("db").Collection("recipes")
	parsedDate, _ := time.Parse("2006-01-02", c.PostForm("date"))

	filter := bson.D{{"filename", c.Query("filename")}}
	update := bson.D{{"$set", bson.D{
		{"name", c.PostForm("name")},
		{"description", c.PostForm("description")},
		{"field", c.PostForm("field")},
		{"date", parsedDate.Format("2006-01-02")},
	}}}

	_, err := recipesDB.UpdateOne(c, filter, update)
	if err != nil {
		panic("error updating recipe")
	}
}

func deleteRecipe(mongoClient *mongo.Client, c *gin.Context) {
	recipe := getRecipeByFilename(mongoClient, c, c.Query("filename"))
	recipesDB := mongoClient.Database("db").Collection("recipes")
	filter := bson.D{{"_id", recipe.ID}}
	_, err := recipesDB.DeleteOne(c, filter)
	if err != nil {
		panic("error deleting recipe")
	}
}

func getRecipeByFilename(mongoClient *mongo.Client, c *gin.Context, filename string) Recipe {
	var recipe Recipe
	recipesDB := mongoClient.Database("db").Collection("recipes")

	filter := bson.D{{"filename", filename}}

	fmt.Printf("el filename es: %s", filename)

	err := recipesDB.FindOne(c, filter).Decode(&recipe)
	if err != nil {
		fmt.Printf("err: %w", err)
		panic("error getting recipe")
	}

	return recipe
}

func getRecipeByID(mongoClient *mongo.Client, c *gin.Context, id string) Recipe {
	var recipe Recipe
	recipesDB := mongoClient.Database("db").Collection("recipes")

	filter := bson.D{{"_id", id}}

	fmt.Printf("el id es: %s", id)

	err := recipesDB.FindOne(c, filter).Decode(&recipe)
	fmt.Printf("err: %w", err)
	if err != nil {
		panic("error getting recipe")
	}

	return recipe
}

func getRecipes(mongoClient *mongo.Client, c *gin.Context) []Recipe {
	userId := getHexUserId(mongoClient, c)
	recipesDB := mongoClient.Database("db").Collection("recipes")

	cursor, err := recipesDB.Find(c, bson.D{
		{"user_id", userId},
	})
	if err != nil {
		if err == mongo.ErrNoDocuments {
			panic("recipes not found")
		}
		panic("error getting recipes")
	}

	defer cursor.Close(c)

	var recipes []Recipe
	for cursor.Next(c) {
		var recipe Recipe
		if err := cursor.Decode(&recipe); err != nil {
			panic("Error decoding file")
		}
		recipes = append(recipes, recipe)
	}

	return recipes
}

func getRecipeFile(client *mongo.Client, c *gin.Context) {
	recipe := getRecipeByFilename(client, c, c.Query("filename"))

	c.Header("Content-Disposition", "attachment; filename="+recipe.Filename)
	c.Header("Content-Type", "application/octet-stream")
	c.Data(http.StatusOK, "application/octet-stream", recipe.Data)
}

func createRecipe(c *gin.Context, userId string, fileData []byte, fileName string) Recipe {
	id := userId + "_" + fileName
	parsedDate, _ := time.Parse("2006-01-02", c.PostForm("date"))

	recipe := Recipe{
		ID:          id,
		UserID:      userId,
		Data:        fileData,
		Filename:    fileName,
		Name:        c.PostForm("name"),
		Field:       c.PostForm("field"),
		Description: c.PostForm("description"),
		Date:        parsedDate.Format("2006-01-02"),
	}

	return recipe
}

func saveRecipeIntoDB(mongoClient *mongo.Client, c *gin.Context, recipe Recipe) {
	recipesDb := mongoClient.Database("db").Collection("recipes")

	_, err := recipesDb.InsertOne(c, recipe)
	if err != nil {
		panic("Error inserting file into MongoDB")
	}
}
