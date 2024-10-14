package gameLib

import (
	"fmt"
	"log"
	"os"
	"strings"

	"github.com/golang/freetype/truetype"
	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type resource struct {
	Textures map[string]*ebiten.Image
	Fonts    map[string]*truetype.Font
}

func newResource() *resource {
	p := new(resource)
	p.Textures = make(map[string]*ebiten.Image)
	p.Fonts = make(map[string]*truetype.Font)
	return p
}

var Resources *resource = newResource()

func (r *resource) LoadTexturesDir(directory string) {
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
			_, ok := r.Textures[file.Name()]
			if !ok {
				r.Textures[file.Name()], _, err = ebitenutil.NewImageFromFile(file.Name())
			} else {
				fmt.Println("\033[33mWARNING: the texture " + file.Name() + " is already loaded, skipping.\033[0m")
			}
			if err != nil {
				log.Fatal(err)
			}
		}
	}

	count := strings.Count(directory, "/")

	os.Chdir(strings.Repeat(".."+"/", count))
}

func (r *resource) LoadFontsDir(directory string) {
	os.Getwd()
	os.Chdir(directory)
	files, err := os.ReadDir(".")
	if err != nil {
		log.Fatal(err)
	}

	for _, file := range files {

		if file.IsDir() {
			r.LoadFontsDir("./" + file.Name())
		}
		if strings.Contains(file.Name(), ".ttf") {
			_, ok := r.Fonts[file.Name()]
			if !ok {
				font, err := os.ReadFile(file.Name())
				if err != nil {
					log.Fatal(err)
				}
				r.Fonts[file.Name()], err = truetype.Parse(font)
				if err != nil {
					log.Fatal(err)
				}
			} else {
				fmt.Println("\033[33mWARNING: the font " + file.Name() + " is already loaded, skipping.\033[0m")
			}
			if err != nil {
				log.Fatal(err)
			}
		}
	}

	count := strings.Count(directory, "/")

	os.Chdir(strings.Repeat(".."+"/", count))
}
