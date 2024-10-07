package main

import "github.com/hajimehoshi/ebiten/v2"

type Drawable interface {
	Draw(*ebiten.Image) error
}

type EventHandler interface {
	Handle() error
}
