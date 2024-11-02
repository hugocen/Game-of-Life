import argparse
from cv2 import cv2 as cv 
import numpy as np
from scipy import signal
import keyboard

class GameofLife:
    def __init__(self, args):
        self.game_height = args.game_height
        self.game_width = args.game_width
        self.seed = args.seed
        self.display_height = args.display_height
        self.display_width = args.display_width
        self.img = np.zeros([self.game_width,self.game_height])

        self.filte = np.full((3, 3), 1)
        self.filte[1][1] = 0

    def init(self, img, k):
        for _ in range(k):
            img[np.random.randint(len(img))][np.random.randint(len(img[0]))] = 1
        return img

    def evol(self, img):
        evaluation = signal.convolve2d(img, self.filte, mode='same')
        for i in range(len(img)):
            for j in range(len(img[0])):
                if img[i][j] == 1 and evaluation[i][j] < 2:
                    img[i][j] = 0
                elif img[i][j] == 1 and (evaluation[i][j] == 2 or evaluation[i][j] == 3):
                    pass
                elif img[i][j] == 1 and evaluation[i][j] > 3:
                    img[i][j] = 0
                elif img[i][j] == 0 and evaluation[i][j] == 3:
                    img[i][j] = 1
        return img


    def run(self):
        self.img = self.init(self.img, self.seed)
        while True:
            cv.imshow('Game of Life', cv.resize(
                self.img, 
                (self.display_width,  self.display_height), 
                interpolation=cv.INTER_AREA))
            self.img = self.evol(self.img)

            if cv.waitKey(1) & keyboard.is_pressed('Esc'):
                break

        cv.destroyAllWindows()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-s", "--seed", type=int, default=3000,
                    help="number of random life dor the initial state")
    parser.add_argument("-gh", "--game_height", type=int, default=150,
                    help="height of the game map")
    parser.add_argument("-gw", "--game_width", type=int, default=200,
                    help="width of the game map")
    parser.add_argument("-dh", "--display_height", type=int, default=750,
                    help="height of the display window")
    parser.add_argument("-dw", "--display_width", type=int, default=1000,
                    help="width of the display window")
    args = parser.parse_args()
    a = GameofLife(args)
    a.run()
