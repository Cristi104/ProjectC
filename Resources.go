package main

import (
	"log"
	"os"
	"strings"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type Resource struct {
	Textures map[string]*ebiten.Image
}

func NewResource() *Resource {
	p := new(Resource)
	p.Textures = make(map[string]*ebiten.Image)
	return p
}

var resource Resource = *NewResource()

func (r *Resource) LoadTexturesDir(directory string) {
	os.Getwd()
	os.Chdir(directory)
	files, err := os.ReadDir(".")
	if err != nil {
		log.Fatal(err)
	}

	for _, file := range files {

		if file.IsDir() {
			r.LoadTexturesDir("./" + file.Name())
		}
		if strings.Contains(file.Name(), ".png") {
			r.Textures[file.Name()], _, err = ebitenutil.NewImageFromFile(file.Name())
			if err != nil {
				log.Fatal(err)
			}
		}
	}

	count := strings.Count(directory, "/")

	os.Chdir(strings.Repeat(".."+"/", count))
}
