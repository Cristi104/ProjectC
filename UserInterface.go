package main

import (
	"fmt"

	"github.com/hajimehoshi/ebiten/v2"
)

type Button struct {
	Image     *ebiten.Image
	posX      float64
	posY      float64
	transform ebiten.DrawImageOptions
	pressed   bool
	OnClick   func()
}

func makeButton(posX, posY float64) Button {
	var button Button
	button.Image = Resources.Textures["Button.png"]
	button.posX = posX
	button.posY = posY
	button.Update()
	return button
}

func (b *Button) Update() {
	b.transform.GeoM.Translate(b.posX, b.posY)
}

func (b *Button) Draw(target *ebiten.Image) {
	target.DrawImage(b.Image, &b.transform)
}

func (b *Button) Handle() {
	pressed := ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft)
	if b.pressed && !pressed {
		mousePosX, mousePosY := ebiten.CursorPosition()
		rect := b.Image.Bounds()
		rect.Min.X += int(b.posX)
		rect.Min.Y += int(b.posY)
		rect.Max.X += int(b.posX)
		rect.Max.Y += int(b.posY)
		if (rect.Min.X < mousePosX && mousePosX < rect.Max.X) && (rect.Min.Y < mousePosY && mousePosY < rect.Max.Y) {
			if b.OnClick != nil {
				b.OnClick()
			} else {
				fmt.Println("\033[33mWARNING: Button is missing OnClick function.\033[0m")
			}
		}
	}
	b.pressed = pressed
}
