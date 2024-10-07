package main

import (
	"log"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

type Game struct {
	button Button
}

func (g *Game) Update() error {
	g.button.Handle()
	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	ebitenutil.DebugPrint(screen, "Hello, World!")
	g.button.Draw(screen)
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (screenWidth, screenHeight int) {
	// return 480, 270
	return 240, 135
}

func main() {
	Resources.LoadTexturesDir("./res/textures")
	Resources.LoadTexturesDir("./res/textures")
	ebiten.SetWindowSize(1600, 900)
	ebiten.SetWindowTitle("Hello, World!")
	game := &Game{}
	game.button = makeButton(20, 20)
	if err := ebiten.RunGame(game); err != nil {
		log.Fatal(err)
	}
}
