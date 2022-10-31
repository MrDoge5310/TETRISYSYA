from pygame import *


class GameSprite(sprite.Sprite):
    def __init__(self, player_image, player_x, player_y, player_speed):
        sprite.Sprite.__init__(self)
        self.image = transform.scale(image.load(player_image), (100, 100))
        self.speed = player_speed
        self.rect = self.image.get_rect()
        self.rect.x = player_x
        self.rect.y = player_y

    def reset(self):
        window.blit(self.image, (self.rect.x, self.rect.y))

    def move(self, x, y):
        self.rect.x += x
        self.rect.y += y


width = 1000
high = 750
clock = time.Clock()
FPS = 60

window = display.set_mode((width, high))
display.set_caption("Test")

bg = transform.scale(image.load("bg.png"), (width, high))

Plane = GameSprite("plane.png", width / 2, high - 100, 10)
Shar1 = GameSprite("shar.png", width / 3, 0, 10)
Shar2 = GameSprite("shar.png", width / 2 / 3, 200, 10)
Shar3 = GameSprite("shar.png", width - width / 4, 200, 10)

planes = sprite.Group()
baloons = sprite.Group()
planes.add(Plane)
baloons.add(Shar1, Shar2, Shar3)

game = True
while game:

    keys_pressed = key.get_pressed()

    if keys_pressed[K_UP] and (Plane.rect.y - 10) > 0:
        Plane.move(0, -10)

    if keys_pressed[K_DOWN] and (Plane.rect.y + 10) < high-100:
        Plane.move(0, 10)

    if keys_pressed[K_LEFT] and (Plane.rect.x - 10) > 0:
        Plane.move(-10, 0)

    if keys_pressed[K_RIGHT] and (Plane.rect.x + 10) < width-100:
        Plane.move(10, 0)

    for e in event.get():
        if e.type == QUIT:
            game = False

    window.blit(bg, (0, 0))
    Plane.reset()
    Shar1.reset()
    Shar2.reset()
    Shar3.reset()
    display.update()
    clock.tick(FPS)
