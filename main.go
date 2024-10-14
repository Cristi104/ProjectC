package main

import (
	"log"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"

	"github.com/Cristi104/ProjectC/gameLib"
)

type Game struct {
	button gameLib.Button
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
	return 480, 270
	// return 240, 135
}

func main() {
	gameLib.Resources.LoadTexturesDir("./res/textures")
	gameLib.Resources.LoadTexturesDir("./res/textures")
	gameLib.Resources.LoadFontsDir("./res/fonts")
	ebiten.SetWindowSize(1600, 900)
	ebiten.SetWindowTitle("Hello, World!")
	game := &Game{}
	game.button = gameLib.MakeButton(20, 20)
	game.button.Update()
	// game.button.OnClick = func() { fmt.Println("button pressed\n") }
	if err := ebiten.RunGame(game); err != nil {
		log.Fatal(err)
	}
}
