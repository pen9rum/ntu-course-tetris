#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
const int fieldWidth = 10;
const int fieldHeight = 20;
int blocksDropped = 0;
enum class Type {
	None,
	O,
	I,
	T,
	L,
	SL,
	SZ,
	Z,
};
bool isGameOver(const Type field[fieldWidth][fieldHeight])
{
	if (blocksDropped < 10) return false;
	for (int x = 0; x < fieldWidth; x++) {
		if (field[x][0] != Type::None) {
			return true;
		}
	}
	return false;
}
int main() {

	
	int score = 0;
	Type field[fieldWidth][fieldHeight] = {};
	
	sf::Font font;
	if (!font.loadFromFile("path/to/font.ttf")) {  
		return EXIT_FAILURE;
	}
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24); 
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10);
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture yellowTexture;
	if (!yellowTexture.loadFromFile("yellow.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture purpleTexture;
	if (!purpleTexture.loadFromFile("purple.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture orangeTexture;
	if (!orangeTexture.loadFromFile("orange.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture redTexture;
	if (!redTexture.loadFromFile("red.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture lightBlueTexture;
	if (!lightBlueTexture.loadFromFile("light_blue.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture greenTexture;
	if (!greenTexture.loadFromFile("green.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture blueTexture;
	if (!blueTexture.loadFromFile("blue.png")) {
		return EXIT_FAILURE;
	}

	std::map<Type, std::vector<std::vector<sf::Vector2i>>> shapes = {
		{
			Type::O,
			{
			// O:     OO    (0,-1) (1,-1)
			//        OO    (0, 0) (1, 0)
			{
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(0,-1),
				sf::Vector2i(1,-1),
			}
		},
	},
	{
		Type::I,
		{
			// I:     OOOO   (-1, 0) (0, 0) (1,0) (2,0)  shape_Is[0]
			{
				sf::Vector2i(-1, 0),
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
			},
			// I:     O   (0,-2)                         shape_Is[1]
			//        O   (0,-1)
			//        O   (0, 0)
			//        O   (0, 1)
			{
				sf::Vector2i(0,-2),
				sf::Vector2i(0,-1),
				sf::Vector2i(0, 0),
				sf::Vector2i(0, 1),
			}
		}
	},
			{
		Type::L,
		{
			// L:  OO  (0,-2) (-1,-2)
			//        O    (0,-1)
			//        O    (0, 0)
			{
				sf::Vector2i(0, -2),
				sf::Vector2i(-1, -2),
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
			},
			// L:          O                  (0,-1)
			//        OOO  (0, 0) (1,0) (2,0)
			{
				sf::Vector2i(2, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
			},
			// L:     O    (0,-2)
			//        O    (0,-1)
			//        OO   (0, 0) (1,0)
			{
				sf::Vector2i(0, -2),
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
			},
			// L:     OOO  (0, 0) (1,0) (2,0)
			//         O   (0, 1)
			{
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
				sf::Vector2i(0, 1),
			},
		}
	},
		{
		Type::SL,
		{
			// L:     OO   (0,-2) (1,-2)
			//        O    (0,-1)
			//        O    (0, 0)
			{
				sf::Vector2i(0, -2),
				sf::Vector2i(1, -2),
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
			},
			// L:     O    (0,-1)
			//        OOO  (0, 0) (1,0) (2,0)
			{
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
			},
			// L:        O    (0,-2)
			//           O    (0,-1)
			//        OO   (0, 0) (-1,0)
			{
				sf::Vector2i(0, -2),
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(-1, 0),
			},
			// L:     OOO  (0, 0) (1,0) (2,0)
			//              O    (2, 1)
			{
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
				sf::Vector2i(2, 1),
			},
		}
	},
		{
		Type::SZ,
		{
				// L:OO   (0,-1) (-1,-1)
				//      OO   (1,0),(0,0)

				{
					sf::Vector2i(0, -1),
					sf::Vector2i(-1, -1),
					sf::Vector2i(1, 0),
					sf::Vector2i(0, 0),
				},
				// L:        O    (1,-1)
				//        OO  (0, 0) (1,0)
				//        O            (0,1)
				{
					sf::Vector2i(0, 1),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(1, -1),
				},

			}
		},
			{
		Type::Z,
		{
					// L:     OO   (0,-1) (1,-1)
					//      OO   (-1,0)(0,0)
				
					{
						sf::Vector2i(0, 0),
						sf::Vector2i(1, -1),
						sf::Vector2i(-1, 0),
						sf::Vector2i(0, -1),
					},
					// L:     O    (0,-1)
					//        OO  (0, 0) (1,0)
					//           O            (1,1)
					{
						sf::Vector2i(0, -1),
						sf::Vector2i(0, 0),
						sf::Vector2i(1, 0),
						sf::Vector2i(1, 1),
					},
					
				}
			},

	{
		Type::T,
		{
			// T:     OOO  (0, 0) (1,0) (2,0)
			//           O  (1, 1)
			{
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
				sf::Vector2i(1, 1),
			},
			// T:     O    (0,-1)
			//        OO   (0, 0) (-1,0)
			//        O    (0, 1)
			{
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(-1, 0),
				sf::Vector2i(0, 1),
			},
			// T:     O    (1,-1)
			//        OOO  (0, 0) (1,0) (2,0)
			{
				sf::Vector2i(1, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(2, 0),
			},
			// T:     O    (0,-1)
			//        OO   (0, 0) (1,0)
			//        O    (0, 1)
			{
				sf::Vector2i(0, -1),
				sf::Vector2i(0, 0),
				sf::Vector2i(1, 0),
				sf::Vector2i(0, 1),
			},
		}
	},
	};

	
	Type currentType = Type(rand() % 7 + 1);
	
	int currentIndex = 0;
	
	const int blockWidth = yellowTexture.getSize().x;
	const int blockHeight = yellowTexture.getSize().y;

	const int windowWidth = fieldWidth * blockWidth;
	const int windowHeight = fieldHeight * blockHeight;
	
	bool gameOver = false;
	std::map<Type, sf::Sprite> sprites = {
		{Type::O, sf::Sprite(yellowTexture)},
		{Type::I, sf::Sprite(lightBlueTexture)},
		{Type::L, sf::Sprite(orangeTexture)},
		{Type::T, sf::Sprite(purpleTexture)},
		{Type::Z, sf::Sprite(redTexture)},
		{Type::SL, sf::Sprite(blueTexture)},
		{Type::SZ, sf::Sprite(greenTexture)},
	};

	backgroundTexture.setRepeated(true);
	sf::Sprite backgroundSprite(
		backgroundTexture,
		sf::IntRect(0, 0, windowWidth, windowHeight));

	std::vector<sf::Vector2i> currentShape;
	sf::Sprite currentSprite;

	const sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), L"俄羅斯方塊");
	sf::Clock clock;
	while (window.isOpen()) {
		gameOver = isGameOver(field);
		currentShape = shapes[currentType][currentIndex];
		currentSprite = sprites[currentType];
		if (gameOver) {
			std::stringstream ss;
			ss << "Game Over! Score: " << score;
			scoreText.setString(ss.str());

			window.clear();
			window.draw(scoreText);
			window.display();
			sf::sleep(sf::seconds(2));
			break;
		}
		enum class Action {
			Hold,
			MoveDown,
			MoveLeft,
			MoveRight,
			Rotate,
		};
		Action action = Action::Hold;
		sf::Event evt;
		if (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				switch (evt.key.code) {
				case sf::Keyboard::Left:
					action = Action::MoveLeft;
					break;
				case sf::Keyboard::A:
					action = Action::MoveLeft;
					break;
				case sf::Keyboard::Down:
					action = Action::MoveDown;
					break;
				case sf::Keyboard::Right:
					action = Action::MoveRight;
					break;
				case sf::Keyboard::Up:
					action = Action::Rotate;
					break;
				}
			}
		}
		blocksDropped++;
		if (clock.getElapsedTime().asSeconds() >= 0.3f) {
			action = Action::MoveDown;
			clock.restart();
		}
		
		sf::Vector2i nextPos(pos);
		int nextIndex = currentIndex;
		if (action == Action::Rotate) {
			// 0 => 1 => 0 => 1 ...
			nextIndex = (nextIndex + 1) % shapes[currentType].size();
		}
		std::vector<sf::Vector2i> nextShape = shapes[currentType][nextIndex];
		switch (action) {
		case Action::Hold:
			break;
		case Action::MoveDown:
			nextPos.y++;
			break;
		case Action::MoveLeft:
			nextPos.x--;
			break;
		case Action::MoveRight:
			nextPos.x++;
			break;
		}

		int countEmpty = 0;
		for (const sf::Vector2i d : nextShape) {
			sf::Vector2i np = nextPos + d;
			if (np.x >= 0 && np.x < fieldWidth &&
				np.y < fieldHeight &&
				(np.y < 0 || field[np.x][np.y] == Type::None)) {
				countEmpty++;
			}
		}
		int linesCleared = 0;
		if (countEmpty == 4) {
			pos = nextPos;
			currentIndex = nextIndex;
			currentShape = nextShape;
		}
		else {
			if (action == Action::MoveDown) {
				for (const sf::Vector2i& d : currentShape) {
					sf::Vector2i np = pos + d;
					if (np.y >= 0) {
						field[np.x][np.y] = currentType;
					}
				}

				for (int y = 0; y < fieldHeight; y++) {
					bool isFull = true;
					for (int x = 0; x < fieldWidth; x++) {
						if (field[x][y] == Type::None) {
							isFull = false;
							break;
						}
					}
					if (isFull) {
						linesCleared++;
						for (int ty = y; ty > 0; ty--) {
							for (int x = 0; x < fieldWidth; x++) {
								field[x][ty] = field[x][ty - 1];
							}
						}
						for (int x = 0; x < fieldWidth; x++) {
							field[x][0] = Type::None;
						}
					}
				}

				switch (linesCleared) {
				case 1: score += 100; break;
				case 2: score += 300; break;
				case 3: score += 600; break;
				case 4: score += 1000; break;
				default: break;  
				}
				pos = origin;
				currentType = Type(rand() % 7+ 1);
				currentIndex = 0;
				currentShape = shapes[currentType][currentIndex];
				currentSprite = sprites[currentType];
			}
		}
		window.clear();

		window.draw(backgroundSprite);

		// 繪製背景的場地
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				if (field[x][y] == Type::None) continue;

				sf::Sprite& s = sprites[field[x][y]];

				s.setPosition(
					float(x * blockWidth),
					float(y * blockHeight));
				window.draw(s);
			}
		}

		// 繪製控制的物體
		// O:     OO    (0,-1) (1,-1)
		//        OO    (0, 0) (1, 0)
		for (const sf::Vector2i& d : currentShape) {
			sf::Vector2i np = pos + d;
			currentSprite.setPosition(
				float(np.x * blockWidth),
				float(np.y * blockHeight));
			window.draw(currentSprite);
		}
		
		
		window.display();
	}
	return EXIT_SUCCESS;
}