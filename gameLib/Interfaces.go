package gameLib

import "github.com/hajimehoshi/ebiten/v2"

type Drawable interface {
	Draw(*ebiten.Image)
}

type EventHandler interface {
	Handle() error
}
