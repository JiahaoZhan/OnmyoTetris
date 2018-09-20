#include "gameFrame.hpp"
#include "Config.hpp"

	GameFrame::GameFrame()
	{
		window = new RenderWindow(VideoMode(1136, 768.0), "Tetris");
		window->setFramerateLimit(MAX_FRAME_RATE);
		window->setKeyRepeatEnabled(true);
		window->setVerticalSyncEnabled(true);
		clock = new Clock();
		pause = false;
		timer = 0;
		timeElapsed = 0;
	}

	GameFrame::GameFrame(double width, double height)
	{
		window = new RenderWindow(VideoMode(1136, 768), "Tetris");
		window->setFramerateLimit(MAX_FRAME_RATE);
		window->setKeyRepeatEnabled(false);
		clock = new Clock();
		pause = false;
		timer = 0;
		timeElapsed = 0;
	}

	void GameFrame::play()
	{
		srand((unsigned int)time(NULL));
		loadImg();
		loadMusic();
		loadSound();
		loadText();
		this->currT = ranTetromino(rand() % 7);
		this->nextT = ranTetromino(rand() % 7);
		this->putNextTetromino();
		while (window->isOpen())
		{
			Event e;
			timeElapsed = clock->getElapsedTime().asSeconds();
			timer += timeElapsed;
			while (window->pollEvent(e))
			{
				if (e.type == Event::Closed)
					window->close();
		
				if (e.type == Event::KeyPressed)
					controlPanel(e);

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					cout << "Left button is pressed" << endl;
					Vector2i mousePos = Mouse::getPosition(*window);
					//cout << "mousePos.x: " << mousePos.x << " mousePos.y: " << mousePos.y << endl;
					//Exit button
					if (mousePos.x >= 562 && mousePos.x <= 662 &&
						mousePos.y >= 657 && mousePos.y <= 745)
					{
						cout << "Exit button is pressed" << endl;
						return;
					}

				}

			}
			autoFalling(rand() % 7);
			drawWindow();
		}
		window->draw(*sprites[9]);
		window->display();
	}

	void GameFrame::drawWindow()
	{
		window->clear(Color::White);

		//Draw sprites
		for (int i = 0; i < IMG_NUM; i++)
		{
			window->draw(*sprites[i]);
		}

		//Draw Cell
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				//Indicates there is a cell in  the corresponding entry
				if (field[i][j] != 0)
					field[i][j]->drawCell(window, i, j);
			}
		}

		//Draw nextTetromino
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (nextTetro[i][j] != 0)
					nextTetro[i][j]->drawNextCell(window, i, j);
			}
		}
		
		//Draw Text
		for (int i = 0; i < TEXT_NUM; i++)
		{
			window->draw(*texts[i]);
		}

		

		window->display();

	}
	
	bool GameFrame::isRowEmpty(int row)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (field[row][j] == 0)
				return true;
		}
		return false;
	}

	void GameFrame::setRowEmpty(int row)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			//Set the full row to be empty
			delete field[row][j];
			field[row][j] = 0;
		}
		getScore->play();
	}

	void GameFrame::copyRow(int dstRow, int srcRow)
	{
		if (isRowEmpty(srcRow) || srcRow <= 0) return;
	
		for (int i = 0; i < WIDTH; i++)
		{
			//Copying the row
			field[dstRow][i] = field[srcRow][i];
			copyRow(srcRow, srcRow - 1);
		}

		copyRow(dstRow, srcRow);
	}

	void GameFrame::moveDown(int row)
	{
		for (int i = row; i > 0; i--)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				field[i][j] = field[i - 1][j];
			}
		}

		if (!isRowEmpty(row))
			moveDown(row);
		else return;
	}

	void GameFrame::cancelLine()
	{
		bool full = true;

		for (int i = HEIGHT - 1; i > 0; i--)
		{
			if (isRowEmpty(i))
				full = false;

			//if the row is full
			if (full)
			{	
				moveDown(i);
				getScore->play();
			}

			else full = true;	
		}
	}

	void GameFrame::controlPanel(Event e)
	{
		switch (e.key.code)
		{
		case (Keyboard::Up) :
			//O shape cannot be rotated
			if (currT->shape == 'O' || pause) break;
			moveAction->play();
			this->clearTetromino();
			currT->rotate(field);
			this->putTetromino();
			break;

		case (Keyboard::Left) :
			//Boundary check 
			if (pause) break;
			moveAction->play();
			this->clearTetromino();
			currT->moveLeft(field);
			this->putTetromino();
			break;

		case (Keyboard::Right) :
			//Boundary check
			if (pause) break;
			if (currT->cells[3]->getX() + 1 > WIDTH) break;
			moveAction->play();
			this->clearTetromino();
			currT->moveRight(field);
			this->putTetromino();
			break;

		case(Keyboard::Down) :
			//Boundary check
			if (pause) break;
			moveAction->play();
			this->clearTetromino();
			currT->moveDown(field);
			this->putTetromino();
			break;

		case(Keyboard::P) :
			if (!pause)
			{
				bgMusic->pause();
				pause = true;
			}
			else
			{
				bgMusic->play();
				pause = false;
			}
			break;
		}
	}

	void GameFrame::autoFalling(int code)
	{
		if (timer >= DELAY && !pause)
		{
			timer = 0;
			clock->restart();
			this->clearTetromino();
			if (!currT->moveDown(field))
			{	
				this->putTetromino();
				//store the cells of the currT in the field and send the next Tetromino
				hitCell->play();

				cancelLine();

				*currT = *nextT;
				
				if (!this->putTetromino())
				{
					cout << "GameOver" << endl;
					return;
				}
				this->clearNextTetromino();
				nextT = ranTetromino(code);
				this->putNextTetromino();
			}
			else
			{
				this->putTetromino();
				
			}
		}
	}

	Tetromino * GameFrame::ranTetromino(int code)
	{
		switch (code)
		{
		case 0:
			return new I(Iimg);
			break;
		case 1:
			return new Z(Zimg);
			break;
		case 2:
			return new S(Simg);
			break;
		case 3:
			return new T(Timg);
			break;
		case 4:
			return new L(Limg);
			break;
		case 5:
			return new J(Jimg);
			break;
		case 6:
			return new O(Oimg);
			break;
		}
	}
	
	void GameFrame::clearTetromino()
	{
		for (int i = 0; i < 4; i++)
		{
			Cell *tmpCell = currT->cells[i];
			field[tmpCell->getY()][tmpCell->getX()] = 0;
		}
	}

	void GameFrame::clearNextTetromino()
	{
		for (int i = 0; i < 4; i++)
		{
			Cell *tmpCell = nextT->cells[i];
			nextTetro[tmpCell->getY()][tmpCell->getX()] = 0;
		}
	}

	bool GameFrame::putTetromino()
	{
		for (int i = 0; i < 4; i++)
		{
			Cell *tmpCell = currT->cells[i];
			if (field[tmpCell->getY()][tmpCell->getX()] != 0)
				return false;
		}

		for (int i = 0; i < 4; i++)
		{
			Cell *tmpCell = currT->cells[i];
			field[tmpCell->getY()][tmpCell->getX()] = tmpCell;
		}

		return true;
	}

	void GameFrame::putNextTetromino()
	{
		for (int i = 0; i < 4; i++)
		{
			Cell *tmpCell = nextT->cells[i];
			nextTetro[tmpCell->getY()][tmpCell->getX()] = tmpCell;
		}
	}

	void GameFrame::loadSound()
	{
		if (!scoreBuffer.loadFromFile(mkDir("getScore.wav", sound)))
		{
			cout << "Fail to load the score sound" << endl;
			return;
		}

		if (!hitBuffer.loadFromFile(mkDir("hit.wav", sound)))
		{
			cout << "Fail to load the hit sound" << endl;
			return;
		}

		if (!moveBuffer.loadFromFile(mkDir("moveAction.wav", sound)))
		{
			cout << "Fail to load the rotate sound" << endl;
			return;
		}

		moveAction = new Sound();
		hitCell = new Sound();
		getScore = new Sound();
		moveAction->setBuffer(moveBuffer);
		moveAction->setPitch(0.5);
		moveAction->setVolume(20);

		hitCell->setBuffer(hitBuffer);
		getScore->setBuffer(scoreBuffer);
	}

	void GameFrame::loadMusic()
	{
		bgMusic = new Music();
		// Open it from an audio file
		if (!bgMusic->openFromFile(mkDir("playing.ogg", music)))
		{
			cout << "Fail to load the background music" << endl;
			return;
		}

		bgMusic->setPosition(0, 1, 10); // change its 3D position
		bgMusic->setPitch(1);           // increase the pitch
		bgMusic->setVolume(30);         // reduce the volume
		bgMusic->setLoop(true);         // make it loop
		// Play it
		bgMusic->play();
	}

	void GameFrame::loadText()
	{
		fontColor = new Color(0, 0, 0);
		textFont = new Font();
		
		if (!textFont->loadFromFile(mkDir("CHILLER.ttf", font)))
		{
			cout << "Fail to load the font file" << endl;
			return;
		}

		Title = new Text("Tetris", *textFont, 100);
		Level = new Text("Level", *textFont, 44);
		Pause = new Text("Pause & Resume", *textFont, 44);
		Exit = new Text("Exit", *textFont, 44);

		//TitleFont
		Title->setFillColor(*fontColor);
		Title->setStyle(Text::Bold);
		Title->setPosition(70, 30);
		//LevelFont
		Level->setFillColor(*fontColor);
		Level->setStyle(Text::Bold);
		Level->setPosition(114, 683);
		//PauseFont
		Pause->setFillColor(*fontColor);
		Pause->setStyle(Text::Bold);
		Pause->setPosition(328, 683);
		//ExitFont
		Exit->setFillColor(*fontColor);
		Exit->setStyle(Text::Bold);
		Exit->setPosition(662, 683);

		texts.push_back(Title);
		texts.push_back(Level);
		texts.push_back(Pause);
		texts.push_back(Exit);

	}

	void GameFrame::loadImg()
	{
		fieldImg = new Texture();
		scrollImg = new Texture();
		grid = new Texture();
		bottom = new Texture();
		scoreBoard = new Texture();
		nextTetroFrame = new Texture();
		gameOver = new Texture();
		pauseText = new Texture();
		exit = new Texture();
		level = new Texture();
		Iimg = new Texture();
		Jimg = new Texture();
		Simg = new Texture();
		Zimg = new Texture();
		Limg = new Texture();
		Oimg = new Texture();
		Timg = new Texture();

		if (!fieldImg->loadFromFile(mkDir("Background.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!scrollImg->loadFromFile(mkDir("Scroll.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!grid->loadFromFile(mkDir("grid.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!bottom->loadFromFile(mkDir("Bottom.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!scoreBoard->loadFromFile(mkDir("scoreBoard.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!nextTetroFrame->loadFromFile(mkDir("nextTetromino.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl; 
			return;
		}
		if (!gameOver->loadFromFile(mkDir("GameOver.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!pauseText->loadFromFile(mkDir("Pause.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!exit->loadFromFile(mkDir("Exit.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}
		if (!level->loadFromFile(mkDir("Level.png", texture)))
		{
			cout << "Fail to load fieldImg" << endl;
			return;
		}

		if (!Iimg->loadFromFile(mkDir("I.png", texture)))
		{
			cout << "Fail to load I image" << endl;
			return;
		}

		if (!Jimg->loadFromFile(mkDir("J.png", texture)))
		{
			cout << "Fail to load J image" << endl;
			return;
		}

		if (!Simg->loadFromFile(mkDir("S.png", texture)))
		{
			cout << "Fail to load S image" << endl;
			return;
		}

		if (!Zimg->loadFromFile(mkDir("Z.png", texture)))
		{
			cout << "Fail to load Z image" << endl;
			return;
		}

		if (!Limg->loadFromFile(mkDir("L.png", texture)))
		{
			cout << "Fail to load L image" << endl;
			return;
		}

		if (!Oimg->loadFromFile(mkDir("O.png", texture)))
		{
			cout << "Fail to load O image" << endl;
			return;
		}

		if (!Timg->loadFromFile(mkDir("T.png", texture)))
		{
			cout << "Fail to load T image" << endl;
			return;
		}

		sprites.push_back(new Sprite(*fieldImg));
		sprites.push_back(new Sprite(*scrollImg));
		sprites.push_back(new Sprite(*grid));
		sprites.push_back(new Sprite(*bottom));
		sprites.push_back(new Sprite(*scoreBoard));
		sprites.push_back(new Sprite(*nextTetroFrame));
		sprites.push_back(new Sprite(*pauseText));
		sprites.push_back(new Sprite(*exit));
		sprites.push_back(new Sprite(*level));
		sprites.push_back(new Sprite(*gameOver));

		sprites[0]->setTextureRect(IntRect(0, 0, 1136, 768));
		sprites[1]->setTextureRect(IntRect(0, 0, 236, 540));
		sprites[2]->setTextureRect(IntRect(0, 0, 312, 520));
		sprites[3]->setTextureRect(IntRect(0, 0, 1136, 124));
		sprites[4]->setTextureRect(IntRect(0, 0, 312, 768));
		sprites[5]->setTextureRect(IntRect(0, 0, 198, 187));
		sprites[6]->setTextureRect(IntRect(0, 0, 100, 88));
		sprites[7]->setTextureRect(IntRect(0, 0, 100, 88));
		sprites[8]->setTextureRect(IntRect(0, 0, 100, 88));
		sprites[9]->setTextureRect(IntRect(0, 0, 1136, 768));

		sprites[0]->setPosition(0.0, 0.0);
		sprites[1]->setPosition(1136-236-52, 52);
		sprites[2]->setPosition(442, 72);
		sprites[3]->setPosition(0.0, 644.0);
		sprites[4]->setPosition(0.0, 0.0);
		sprites[5]->setPosition(60.0, 344.0);
		sprites[6]->setPosition(218.0, 657.0);
		sprites[7]->setPosition(562.0, 657.0); //Exit
		sprites[8]->setPosition(26.0, 657.0);

		//Whenever the game is over, display sprite[9]
		sprites[9]->setPosition(0.0, 0.0);
		sprites[9]->scale(Vector2f(0.823, 1));
	}
