package gameLib

import (
	"fmt"
	"log"
	"os"
	"strings"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type Resource struct {
	Textures map[string]*ebiten.Image
}

func newResource() *Resource {
	p := new(Resource)
	p.Textures = make(map[string]*ebiten.Image)
	return p
}

var Resources *Resource = newResource()

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
