package gameLib

import (
	"fmt"

	"github.com/hajimehoshi/ebiten/v2"
)

type Button struct {
	Image     *ebiten.Image
	PosX      float64
	PosY      float64
	OnClick   func()
	transform ebiten.DrawImageOptions
	pressed   bool
}

func makeButton(posX, posY float64) Button {
	var button Button
	button.Image = Resources.Textures["Button.png"]
	button.PosX = posX
	button.PosY = posY
	button.Update()
	return button
}

func (b *Button) Update() {
	b.transform.GeoM.Reset()
	b.transform.GeoM.Translate(b.PosX, b.PosY)
}

func (b *Button) Draw(target *ebiten.Image) {
	target.DrawImage(b.Image, &b.transform)
}

func (b *Button) Handle() {
	pressed := ebiten.IsMouseButtonPressed(ebiten.MouseButtonLeft)
	if b.pressed && !pressed {
		mousePosX, mousePosY := ebiten.CursorPosition()
		rect := b.Image.Bounds()
		rect.Min.X += int(b.PosX)
		rect.Min.Y += int(b.PosY)
		rect.Max.X += int(b.PosX)
		rect.Max.Y += int(b.PosY)
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
