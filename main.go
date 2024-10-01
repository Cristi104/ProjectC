package main

import (
	"log"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type Game struct{}

var image *ebiten.Image

func (g *Game) Update() error {
	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	ebitenutil.DebugPrint(screen, "Hello, World!")
	screen.DrawImage(image, nil)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	// return 480, 270
	return 240, 135
}

func main() {
	var err error
	Resources.LoadTexturesDir("./res/textures")
	Resources.LoadTexturesDir("./res/textures")
	image, _, err = ebitenutil.NewImageFromFile("res/textures/Button.png")
	if err != nil {
		log.Fatal(err)
	}
	ebiten.SetWindowSize(1600, 900)
	ebiten.SetWindowTitle("Hello, World!")
	if err := ebiten.RunGame(&Game{}); err != nil {
		log.Fatal(err)
	}
}
