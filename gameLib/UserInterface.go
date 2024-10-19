package gameLib

import (
	"fmt"
	"image/color"

	"github.com/golang/freetype/truetype"
	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/text"
	"golang.org/x/image/font"
)

type Button struct {
	Image     *ebiten.Image
	PosX      float64
	PosY      float64
	OnClick   func()
	transform ebiten.DrawImageOptions
	pressed   bool
}

func MakeButton(posX, posY float64) (button Button) {
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

type Text struct {
	PosX float64
	PosY float64
	Font font.Face
	str  string
}

func MakeText(text string, posX, posY float64, font font.Face) (t Text) {
	if text == "" {
		t.str = "New\nText\n"
	} else {
		t.str = text
	}
	if font == nil {
		var opts truetype.Options
		t.Font = Resources.MakeFaceFromFont("arial.ttf", &opts)
	} else {
		t.Font = font
	}
	t.PosX = posX
	t.PosY = posY
	return t
}

func (t *Text) Draw(target *ebiten.Image) {
	text.Draw(target, t.str, t.Font, int(t.PosX), int(t.PosY), color.White)
}
