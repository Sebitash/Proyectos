package main

import (
	"bytes"
	"context"
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strconv"
	"strings"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/jung-kurt/gofpdf"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
)

type ProfileData struct {
	Name        string
	City        string
	Weight      string
	Height      string
	BloodType   string
	Conditions  string
	Allergies   string
	Medications string
}

type Count struct {
	Count int
}

func main() {
	err := StartMongoDbContainer()
	if err != nil {
		log.Fatal("Failed to start mongo db container", err)
		panic(err)
	}
	mongoClient, err := createMongoClient()
	if err != nil {
		log.Fatal("Failed to create mongo db client", err)
		panic(err)
	}

	passwords := map[string]string{}
	passwords["user"] = "user"
	e := gin.Default()

	e.LoadHTMLGlob("templates/*")

	e.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", gin.H{})
	})

	e.GET("/signup", func(c *gin.Context) {
		c.HTML(http.StatusOK, "register.html", gin.H{})
	})

	e.GET("/login", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", gin.H{})
	})

	e.POST("/register", func(c *gin.Context) {
		register(mongoClient, c)
	})

	e.POST("/signin", func(c *gin.Context) {
		email := c.PostForm("username")
		password := c.PostForm("password")
		signIn(mongoClient, c, email, password)
	})

	e.GET("/sidebar", func(c *gin.Context) {
		c.HTML(http.StatusOK, "sidebar.html", gin.H{})
	})

	e.GET("/header", func(c *gin.Context) {

		if userLoggedIn(c) {
			c.HTML(http.StatusOK, "header.html", gin.H{})
		} else {
			c.HTML(http.StatusOK, "header_not_logged.html", gin.H{})
		}
	})

	e.GET("/recover_password", func(c *gin.Context) {

		c.HTML(http.StatusOK, "recover_password.html", gin.H{})
	})

	e.POST("/change_password", func(c *gin.Context) {
		changePassword(mongoClient, c)
	})

	var medicalRecipes []Recipe
	e.GET("/medical_recipes", func(c *gin.Context) {
		defer handePanic(c)
		log.Println("obtaining recipes")
		medicalRecipes = getRecipes(mongoClient, c)
		c.HTML(http.StatusOK, "medical_recipes_view.html", gin.H{"files": medicalRecipes})
	})

	e.GET("/medical_recipe/file", func(c *gin.Context) {
		defer handePanic(c)
		getRecipeFile(mongoClient, c)
	})

	e.GET("/medical_recipe/edit", func(c *gin.Context) {
		defer handePanic(c)
		recipe := getRecipeByFilename(mongoClient, c, c.Query("filename"))
		fmt.Printf("recipe description: %s", recipe.Description)
		c.HTML(http.StatusOK, "edit_medical_recipe.html", gin.H{"file": recipe})
	})

	e.DELETE("/medical_recipe", func(c *gin.Context) {
		log.Println("deleting recipe")
		defer handePanic(c)
		deleteRecipe(mongoClient, c)
		recipes := getRecipes(mongoClient, c)
		c.HTML(http.StatusOK, "medical_recipes_view.html", gin.H{"files": recipes})
	})

	e.PUT("/medical_recipe", func(c *gin.Context) {
		log.Println("updating recipe")
		defer handePanic(c)

		updateRecipe(mongoClient, c)
		recipes := getRecipes(mongoClient, c)
		c.HTML(http.StatusOK, "medical_recipes_view.html", gin.H{"files": recipes})
	})

	e.GET("/medical_recipe/add", func(c *gin.Context) {
		c.HTML(http.StatusOK, "add_medical_recipe.html", gin.H{})
	})

	e.GET("/filter_medical_recipes", func(c *gin.Context) {
		searchValue := c.Query("searchBar")
		scrollableItemsTemplate, err := template.ParseFiles("templates/scrollable_items.html")
		if err != nil {
			c.String(http.StatusInternalServerError, "Error al cargar la plantilla")
			return
		}
		var filteredMedicalRecipes []Recipe
		for _, medicalRecipe := range medicalRecipes {
			if strings.Contains(strings.ToLower(medicalRecipe.Name), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalRecipe.Filename), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalRecipe.Field), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalRecipe.Date), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalRecipe.Description), strings.ToLower(searchValue)) {
				filteredMedicalRecipes = append(filteredMedicalRecipes, medicalRecipe)
			}
		}
		c.Header("Content-Type", "text/html; charset=utf-8")
		scrollableItemsTemplate.Execute(c.Writer, filteredMedicalRecipes)
	})

	e.POST("/recipe", func(c *gin.Context) {
		log.Println("saving recipe")
		defer handePanic(c)
		insertRecipe(mongoClient, c)
		recipes := getRecipes(mongoClient, c)
		c.HTML(http.StatusOK, "medical_recipes_view.html", gin.H{"files": recipes})
	})

	e.GET("/upload_medical_recipe_screen", func(c *gin.Context) {
		c.HTML(http.StatusOK, "upload_medical_recipe.html", gin.H{})
	})

	var medicalStudies []File
	e.POST("/medical_study", func(c *gin.Context) {
		log.Println("saving medical_study")
		defer handePanic(c)
		saveMedicalStudy(mongoClient, c)
		medicalStudies = getUserMedicalStudiesData(mongoClient, c)
		c.HTML(http.StatusOK, "medical_studies_view.html", gin.H{"files": medicalStudies})
	})

	e.DELETE("/medical_study", func(c *gin.Context) {
		log.Println("saving medical_study")
		defer handePanic(c)
		deleteMedicalStudy(mongoClient, c)
		medicalStudies := getUserMedicalStudiesData(mongoClient, c)
		c.HTML(http.StatusOK, "medical_studies_view.html", gin.H{"files": medicalStudies})
	})

	e.GET("/cancel_action", func(c *gin.Context) {
		return
	})

	e.POST("/confirm_action", func(c *gin.Context) {
		// Convierte los parámetros en un gin.H para pasarlos al HTML
		c.HTML(http.StatusOK, "confirm_action.html", gin.H{
			"filename":    c.Query("filename"),
			"action":      c.Query("action"),
			"name":        c.PostForm("name"),
			"type":        c.PostForm("type"),
			"description": c.PostForm("description"),
			"date":        c.PostForm("date"),
			"city":        c.PostForm("city"),
			"weight":      c.PostForm("weight"),
			"height":      c.PostForm("height"),
			"bloodtype":   c.PostForm("bloodtype"),
			"conditions":  c.PostForm("conditions"),
			"allergies":   c.PostForm("allergies"),
			"medications": c.PostForm("medications"),
			"field":       c.PostForm("field"),
		})
	})

	e.POST("/perform_action", func(c *gin.Context) {
		log.Println("dentro de perform_action")
		userId := getHexUserId(mongoClient, c)
		log.Println("DENTRO DE confirm_action")
		log.Println("userId: ", userId)
		filename := c.Query("filename") // Captura el parámetro opcional del filename
		log.Println("filename: ", filename)
		name := c.PostForm("name")
		log.Println("name: ", name)
		defer handePanic(c)
		if c.Query("action") == "update_medical_study" {
			updateMedicalStudy(mongoClient, c)
			medicalStudies := getUserMedicalStudiesData(mongoClient, c)
			c.HTML(http.StatusOK, "medical_studies_view.html", gin.H{"files": medicalStudies})
		} else if c.Query("action") == "delete_medical_study" {
			deleteMedicalStudy(mongoClient, c)
			medicalStudies := getUserMedicalStudiesData(mongoClient, c)
			c.HTML(http.StatusOK, "medical_studies_view.html", gin.H{"files": medicalStudies})
		} else if c.Query("action") == "delete_medical_recipe" {
			deleteRecipe(mongoClient, c)
			recipes := getRecipes(mongoClient, c)
			c.HTML(http.StatusOK, "medical_recipes_view.html", gin.H{"files": recipes})
		} else if c.Query("action") == "update_medical_recipe" {
			updateRecipe(mongoClient, c)
			recipes := getRecipes(mongoClient, c)
			c.HTML(http.StatusOK, "medical_recipes_view.html", gin.H{"files": recipes})
		} else if c.Query("action") == "save_personal_data" {
			savePersonalData(c, mongoClient)
		}
	})

	e.GET("/filter_medical_studies", func(c *gin.Context) {
		searchValue := c.Query("searchBar")
		scrollableItemsTemplate, err := template.ParseFiles("templates/scrollable_items.html")
		if err != nil {
			c.String(http.StatusInternalServerError, "Error al cargar la plantilla")
			return
		}
		var acceptedMedicalStudies []File
		for _, medicalStudy := range medicalStudies {
			if strings.Contains(strings.ToLower(medicalStudy.Name), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalStudy.Filename), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalStudy.Type), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalStudy.Date), strings.ToLower(searchValue)) ||
				strings.Contains(strings.ToLower(medicalStudy.Description), strings.ToLower(searchValue)) {
				acceptedMedicalStudies = append(acceptedMedicalStudies, medicalStudy)
			}
		}
		c.Header("Content-Type", "text/html; charset=utf-8")
		scrollableItemsTemplate.Execute(c.Writer, acceptedMedicalStudies)
	})

	e.GET("/medical_study/file", func(c *gin.Context) {
		defer handePanic(c)
		getMedicalStudyFile(mongoClient, c)
	})

	e.GET("/medical_study/data", func(c *gin.Context) {
		defer handePanic(c)
		getMedicalStudyData(mongoClient, c)
	})

	e.GET("/medical_study/edit", func(c *gin.Context) {
		defer handePanic(c)
		file := getMedicalStudyData(mongoClient, c)
		c.HTML(http.StatusOK, "edit_medical_study.html", gin.H{"file": file})
	})

	e.GET("/medical_studies", func(c *gin.Context) {
		medicalStudies = getUserMedicalStudiesData(mongoClient, c)
		c.HTML(http.StatusOK, "medical_studies_view.html", gin.H{"files": medicalStudies})
	})

	e.GET("/upload_medical_study_screen", func(c *gin.Context) {
		c.HTML(http.StatusOK, "upload_medical_study.html", gin.H{})
	})

	e.GET("/home", func(c *gin.Context) {
		c.HTML(http.StatusOK, "home.html", gin.H{})
	})

	e.GET("/home2", func(c *gin.Context) {
		c.HTML(http.StatusOK, "home2.html", gin.H{})
	})

	e.GET("/logout", func(c *gin.Context) {
		logout(mongoClient, c)
		c.Redirect(http.StatusFound, "/")
	})

	//
	//Datos personales
	//

	e.GET("/datos_personales", func(c *gin.Context) {

		user, err := c.Cookie("user_email")

		if err != nil {
			panic("user_id not found")
		}
		accounts := mongoClient.Database("db").Collection("accounts")
		filter := bson.D{{"email", user}}

		/*
			fmt.Printf("Logged in as %s\n", user)

			appDiagnostics(mongoClient, c)*/

		account := Account{}
		accounts.FindOne(context.TODO(), filter).Decode(&account)

		var displayPersonalInfo = ProfileData{
			Name:        getDefaultValueIfEmpty(account.Name),
			City:        getDefaultValueIfEmpty(account.City),
			Weight:      getDefaultValueIfEmpty(account.Weight),
			Height:      getDefaultValueIfEmpty(account.Height),
			BloodType:   getDefaultValueIfEmpty(account.BloodType),
			Conditions:  getDefaultValueIfEmpty(account.Conditions),
			Allergies:   getDefaultValueIfEmpty(account.Allergies),
			Medications: getDefaultValueIfEmpty(account.Medications),
		}

		es_nuevo_usuario := (strings.TrimSpace(displayPersonalInfo.Name) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.City) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.Weight) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.Height) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.BloodType) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.Conditions) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.Allergies) == "No definido" &&
			strings.TrimSpace(displayPersonalInfo.Medications) == "No definido")

		fmt.Printf("Es nuevo usuario %v\n", es_nuevo_usuario)

		if es_nuevo_usuario {
			c.HTML(http.StatusOK, "personal_data_inicial.html", gin.H{
				"personalInfo": displayPersonalInfo,
			})
		} else {
			c.HTML(http.StatusOK, "personal_data.html", gin.H{
				"personalInfo": displayPersonalInfo,
			})
		}
	})

	e.GET("/datos_personales_editar", func(c *gin.Context) {
		user, err := c.Cookie("user_email")

		if err != nil {
			panic("user_id not found")
		}
		accounts := mongoClient.Database("db").Collection("accounts")
		filter := bson.D{{"email", user}}

		account := Account{}
		accounts.FindOne(context.TODO(), filter).Decode(&account)

		var displayPersonalInfo = ProfileData{
			Name:        getDefaultValueIfEmpty(account.Name),
			City:        getDefaultValueIfEmpty(account.City),
			Weight:      getDefaultValueIfEmpty(account.Weight),
			Height:      getDefaultValueIfEmpty(account.Height),
			BloodType:   getDefaultValueIfEmpty(account.BloodType),
			Conditions:  getDefaultValueIfEmpty(account.Conditions),
			Allergies:   getDefaultValueIfEmpty(account.Allergies),
			Medications: getDefaultValueIfEmpty(account.Medications),
		}

		c.HTML(http.StatusOK, "datos_personales_editar.html", gin.H{
			"personalInfo": displayPersonalInfo,
		})
	})

	e.PUT("/datos_personales_guardar", func(c *gin.Context) {
		savePersonalData(c, mongoClient)
	})

	e.GET("/datos_personales_exportar", func(c *gin.Context) {
		user, err := c.Cookie("user_email")
		if err != nil {
			c.String(http.StatusUnauthorized, "User not found")
			return
		}

		accounts := mongoClient.Database("db").Collection("accounts")
		filter := bson.D{{"email", user}}
		var account Account
		err = accounts.FindOne(context.TODO(), filter).Decode(&account)
		if err != nil {
			c.String(http.StatusInternalServerError, "Error fetching account")
			return
		}

		userData := map[string]string{
			"Nombre":          getDefaultValueIfEmpty(account.Name),
			"Ciudad":          getDefaultValueIfEmpty(account.City),
			"Peso":            getDefaultValueIfEmpty(account.Weight),
			"Altura":          getDefaultValueIfEmpty(account.Height),
			"Grupo Sanguineo": getDefaultValueIfEmpty(account.BloodType),
			"Enfermedades":    getDefaultValueIfEmpty(account.Conditions),
			"Alergias":        getDefaultValueIfEmpty(account.Allergies),
			"Medicacion":      getDefaultValueIfEmpty(account.Medications),
		}

		filename := fmt.Sprintf("datos_%s.pdf", time.Now().Format("20060102150405"))

		// Generate PDF
		var buf bytes.Buffer
		err, buf = generarPDF(userData)
		if err != nil {
			c.String(http.StatusInternalServerError, "Error generating PDF")
			return
		}

		// Set headers and send file
		c.Header("Content-Description", "File Transfer")
		c.Header("Content-Type", "application/octet-stream")
		c.Header("Content-Disposition", fmt.Sprintf("attachment; filename=%s", filename))
		c.Header("Content-Transfer-Encoding", "binary")
		c.Header("Expires", "0")
		c.Header("Cache-Control", "must-revalidate")
		c.Header("Pragma", "public")
		c.Header("Content-Length", strconv.Itoa(buf.Len()))

		c.Data(http.StatusOK, "application/octet-stream", buf.Bytes())
	})

	//Fin datos personales

	e.Run(":8080")
	defer func() {
		if err = mongoClient.Disconnect(context.TODO()); err != nil {
			log.Fatalf("Failed to disconnect from mongodb: %v", err)
		}
	}()
}

func savePersonalData(c *gin.Context, mongoClient *mongo.Client) {
	var valName = c.PostForm("name")
	var valCity = c.PostForm("city")
	var valWeight = c.PostForm("weight")
	var valHeight = c.PostForm("height")
	var valBloodType = c.PostForm("bloodtype")
	var valConditions = c.PostForm("conditions")
	var valAllergies = c.PostForm("allergies")
	var valMedications = c.PostForm("medications")

	user, err := c.Cookie("user_email")

	if err != nil {
		panic("user_id not found")
	}
	accounts := mongoClient.Database("db").Collection("accounts")
	filter := bson.D{{"email", user}}
	update := bson.M{
		"$set": bson.M{
			"Name":        getDefaultValueIfEmptyInverse(valName),
			"City":        getDefaultValueIfEmptyInverse(valCity),
			"medications": getDefaultValueIfEmptyInverse(valMedications),
			"Weight":      getDefaultValueIfEmptyInverse(valWeight),
			"Height":      getDefaultValueIfEmptyInverse(valHeight),
			"BloodType":   getDefaultValueIfEmptyInverse(valBloodType),
			"Conditions":  getDefaultValueIfEmptyInverse(valConditions),
			"Allergies":   getDefaultValueIfEmptyInverse(valAllergies),
		},
	}

	result, err := accounts.UpdateOne(context.TODO(), filter, update)

	if err != nil {
		println("error")
	}

	account := Account{}
	accounts.FindOne(context.TODO(), filter).Decode(&account)

	fmt.Printf("Matched %v documents and updated %v documents.\n", result.MatchedCount, result.ModifiedCount)

	var displayPersonalInfo = ProfileData{
		Name:        getDefaultValueIfEmpty(account.Name),
		City:        getDefaultValueIfEmpty(account.City),
		Weight:      getDefaultValueIfEmpty(account.Weight),
		Height:      getDefaultValueIfEmpty(account.Height),
		BloodType:   getDefaultValueIfEmpty(account.BloodType),
		Conditions:  getDefaultValueIfEmpty(account.Conditions),
		Allergies:   getDefaultValueIfEmpty(account.Allergies),
		Medications: getDefaultValueIfEmpty(account.Medications),
	}

	c.HTML(http.StatusOK, "personal_data.html", gin.H{
		"personalInfo": displayPersonalInfo,
	})
}

func getDefaultValueIfEmpty(value string) string {
	if strings.TrimSpace(value) == "" {
		return "No definido"
	}
	return value
}

func getDefaultValueIfEmptyInverse(value string) string {
	if strings.TrimSpace(value) == "No definido" {
		return ""
	}
	return value
}

func userLoggedIn(c *gin.Context) bool {

	user, err := c.Cookie("user_email")
	fmt.Printf("User logged in: %v, err: %v, userLoggedIn returns: %v\n", user, err, (strings.TrimSpace(user) != ""))
	return (strings.TrimSpace(user) != "")
}

func appDiagnostics(mongoClient *mongo.Client, c *gin.Context) {

	//Ver todas las colecciones en la base
	collectionNames, err := mongoClient.Database("db").ListCollectionNames(context.TODO(), bson.D{})

	if err == nil {
		fmt.Println("Collections found in database:")
		for _, collection := range collectionNames {
			fmt.Println(collection)
		}
	}

	//Ver todos los objetos en una coleccion

	collection := mongoClient.Database("db").Collection("accounts")
	cursor, err := collection.Find(context.TODO(), bson.D{})

	if err != nil {
	}
	defer cursor.Close(context.TODO())

	var accounts []Account

	for cursor.Next(context.TODO()) {
		var account Account
		err := cursor.Decode(&account)
		if err != nil {
		}
		accounts = append(accounts, account)
	}

	fmt.Println("Accounts found:")

	fmt.Println("ID\t\t\t\t\tEmail\t\t\tName\t\tCity\t\tWeight\tHeight\tBloodType\tConditions\tAllergies\tMedications")
	fmt.Println("-----------------------------------------------------------------------------------------------------------")

	// Print each account row
	for _, account := range accounts {
		fmt.Printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
			account.ID, account.Email, account.Name, account.City, account.Weight, account.Height, account.BloodType, account.Conditions, account.Allergies, account.Medications)
	}

}

func generarPDF(data map[string]string) (error, bytes.Buffer) {

	fmt.Printf("generarPDF\n")

	pdf := gofpdf.New("P", "mm", "A4", ".")

	pdf.SetFooterFunc(func() {

		pdf.SetY(-15)
		pdf.SetFont("Helvetica", "I", 12)
		pdf.CellFormat(0, 10, "Generado por Historia Clinica Digital "+time.Now().Format("2006-01-02 15:04:05"), "", 0, "C", false, 0, "")

	})

	pdf.AddPage()

	imagePath := "./img/datosPersonalesExportHeader.png"
	pdf.Image(imagePath, 10, 10, 0, 0, false, "", 0, "")

	pdf.Ln(30)

	pdf.SetFont("Helvetica", "B", 16)
	pdf.Cell(190, 10, "Datos Personales")
	pdf.Ln(15)

	leftMargin := 20.0
	pdf.SetLeftMargin(leftMargin)
	pdf.SetRightMargin(leftMargin)

	titleWidth := 60.0
	valueWidth := 100.0

	titulos := []string{"Nombre", "Ciudad", "Peso", "Altura", "Grupo Sanguineo", "Enfermedades", "Alergias", "Medicacion"}

	for _, value := range titulos {
		pdf.SetFont("Helvetica", "B", 12)
		pdf.CellFormat(titleWidth, 10, value+":", "0", 0, "", false, 0, "")
		pdf.SetFont("Helvetica", "", 12)
		pdf.CellFormat(valueWidth, 10, data[value], "0", 0, "", false, 0, "")
		pdf.Ln(10)
	}

	var buf bytes.Buffer
	var err = pdf.Output(&buf)
	return err, buf
}

func handePanic(c *gin.Context) {
	// detect if panic occurs or not
	a := recover()

	if a != nil {
		fmt.Println("RECOVER", a)
		if a == "user_id not found" {
			c.String(http.StatusBadRequest, "User_id not found")
			return
		}
		if a == "file not found" {
			c.String(http.StatusBadRequest, "File not found")
			return
		}
		if a == "missing file in request" {
			c.String(http.StatusBadRequest, "File not sent in request")
			return
		}
		errMsg := "something went wrong"
		switch v := a.(type) {
		case string:
			errMsg = v // Directly convert if it's a string
		}
		c.String(http.StatusInternalServerError, errMsg)
		return
	}
}
