package main

import (
	"context"
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
)

type Account struct {
	ID       primitive.ObjectID `bson:"_id"`
	Email    string
	Password string

	//Esto eventualmente podria estar en su propio struct
	Name        string
	City        string
	Weight      string
	Height      string
	BloodType   string
	Conditions  string
	Allergies   string
	Medications string
}

func emailIsRegistered(client *mongo.Client, email string) bool {
	coll := client.Database("db").Collection("accounts")

	filter := bson.D{{"email", email}}
	result := Account{}
	err := coll.FindOne(context.TODO(), filter).Decode(&result)
	// si err == nil entonces significa que se encontro una cuenta
	// por lo tanto ese email ya esta registrado
	if err == nil {
		return true
	}
	return false
}

func registerAccount(client *mongo.Client, email, password string) (primitive.ObjectID, error) {
	coll := client.Database("db").Collection("accounts")
	userId := primitive.NewObjectID()
	res, err := coll.InsertOne(context.TODO(), Account{Email: email, Password: password, ID: userId})
	if err != nil {
		fmt.Println("Failed to insert new account into database, error = ", err)
		return userId, err
	}
	fmt.Println("Inserted new account successfully, result = ", res)
	return userId, nil
}

func register(client *mongo.Client, c *gin.Context) {
	email := c.PostForm("username")
	password := c.PostForm("password")

	// Verifica que el email y la contraseña no estén vacíos
	if email == "" || password == "" {
		c.HTML(http.StatusBadRequest, "register.html", gin.H{
			"output": "Email y contraseña son obligatorios.",
		})
		return
	}

	if emailIsRegistered(client, email) {
		c.HTML(http.StatusOK, "register.html", gin.H{
			"output": "El email ya está registrado.",
		})
		return
	}
	userId, err := registerAccount(client, email, password)
	if err != nil {
		c.HTML(http.StatusBadRequest, "register.html", gin.H{
			"output": "Error en la registración.",
		})
		return
	}
	c.SetCookie("user_id", userId.Hex(), 1000000, "", "", true, true)
	c.SetCookie("user_email", email, 1000000, "/", "", true, true)
	c.HTML(http.StatusOK, "home.html", gin.H{
		// Puedes añadir más datos a la respuesta si lo deseas
		"user_id": userId.Hex(),
	})
}

func signIn(client *mongo.Client, c *gin.Context, email, password string) {
	// Verifica que el email y la contraseña no estén vacíos
	if email == "" || password == "" {
		c.HTML(http.StatusOK, "index.html", gin.H{
			"output": "Email y contraseña son obligatorios.",
		})
		return
	}

	accounts := client.Database("db").Collection("accounts")
	account := Account{}
	err := accounts.FindOne(context.TODO(), bson.D{{"email", email}}).Decode(&account)

	if err != nil || account.Password != password {
		c.HTML(http.StatusOK, "index.html", gin.H{
			"output": "Email o contraseña incorrectos.",
		})
		return
	}

	c.SetCookie("user_email", account.Email, 1000000, "/", "", true, true)
	//c.SetCookie("user_id", account.ID.Hex(), 3600*1, "/", "", false, true)

	c.SetCookie("user_id", account.ID.Hex(), 1000000, "", "", true, true)

	// Si las credenciales son correctas, redirige a la página principal o muestra el contenido deseado
	//c.HTML(http.StatusOK, "home.html", nil)
	c.Redirect(http.StatusFound, "/home")
}

func changePassword(client *mongo.Client, c *gin.Context) {
	email := c.PostForm("username")
	password := c.PostForm("password")

	// Verifica que la nueva contraseña no esté vacía
	if password == "" {
		c.HTML(http.StatusOK, "recover_password.html", gin.H{
			"error": "La nueva contraseña no puede estar vacía.",
		})
		return
	}

	accounts := client.Database("db").Collection("accounts")
	account := Account{}
	err := accounts.FindOne(context.TODO(), bson.D{{"email", email}}).Decode(&account)
	if err != nil {
		// El email no está registrado
		fmt.Println("Cuenta encontrada con email = %s => %v", email, account)
		c.HTML(http.StatusOK, "recover_password.html", gin.H{
			"error": "El email no está registrado.",
		})
		return
	}

	filter := bson.D{{"_id", account.ID}}
	update := bson.D{{"$set", bson.D{{"password", password}}}}
	result, err := accounts.UpdateOne(context.TODO(), filter, update)
	if err != nil {
		c.HTML(http.StatusOK, "recover_password.html", gin.H{
			"error": "Hubo un error al actualizar la contraseña.",
		})
		return
	}
	fmt.Println("result = ", result)

	if password != "" {
		c.HTML(http.StatusOK, "recover_password.html", gin.H{
			"output": "La contraseña fue cambiada exitosamente.",
		})
	}

}

func logout(client *mongo.Client, c *gin.Context){
	c.SetCookie("user_email", "", 0, "/", "", true, true)
	c.SetCookie("user_id", "", 0, "/", "", true, true)
}
