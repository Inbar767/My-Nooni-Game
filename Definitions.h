#pragma once

//Screen size
#define SCREEN_WIDTH 864
#define SCREEN_HEIGHT 632

//Egg information
#define NUMBER_EGG 4
#define EGG_WIDTH 64
#define EGG_HEIGHT 82
#define EGG_Y_POSTION 470

//Heart information
#define HEART_WIDTH 64
#define HEART_DIST_PET 6
//heart folder
#define HEART "graphics/Pet/Heart/"

//Toybox corner points
#define TOYBOX_LEFT_X 441
#define TOYBOX_RIGHT_X 533
#define TOYBOX_LEFT_Y 281
#define TOYBOX_RIGHT_Y 382

//Needs information
#define MAX_NEEDS 5
#define NEED_ICON_SIZE 65
#define NEED_SCALE_FRAMES 11
#define NEEDS_CIRCLE_DISTANCE 0.2
//Need scale folder
#define NEED_SCALE "graphics/Needs/"

//Title files
#define LOGO "graphics/Titles/logo.png"
#define WIN_TITLE "graphics/Titles/youWin.png"
#define LOOSE_TITLE "graphics/Titles/gameOver.png"
#define ROOM_TITLE "graphics/Titles/"

//Backgrounds files
#define ROOM_BACKGROUND "graphics/Backgrounds/room.png"
#define YARD_BACKGROUND "graphics/Backgrounds/yard.png"
#define CLASS_BACKGROUND "graphics/Backgrounds/speak.png"
#define CANDY_WINDOW "graphics/Backgrounds/candy.png"
#define MENU_WINDOW "graphics/Backgrounds/menu.png"

//Sounds folders
#define BACKGROUND_SOUND "sounds/Background/"
#define GAME_SOUND "sounds/Game/"
#define ACTION_SOUND "sounds/Action/"
#define SPEAK_SOUNDS "sounds/Words/Speak/"
#define LEARN_SOUND "sounds/Words/Learn/"

//Buttons files
#define BIG_PLAY_BUTTON "graphics/Buttons/play.png"
#define BACK_BUTTON "graphics/Buttons/back.png"
#define PAUSE_BUTTON "graphics/Buttons/pause.png"
#define SOUND_ON "graphics/Buttons/SoundOn.png"
#define SOUND_OFF "graphics/Buttons/SoundOff.png"
#define SPEAK_BUTTON "graphics/Buttons/speak.png"
#define LOCKED_WORD "graphics/Buttons/word_block.png"
#define UNLOCKED_WORD "graphics/Buttons/word.png"
#define LEARNING_WORD "graphics/Buttons/word_learned.png"

//Accessorises information
#define ACCESSORIES_NUBER 4
//Accessorises files
#define REFRIGERATOR_FILE "graphics/Accessories/refrigerator.png"
#define BED_FILE "graphics/Accessories/bed.png"
#define BATH_FILE "graphics/Accessories/bath.png"
#define TABLE_FILE "graphics/Accessories/table.png"
#define OPENED_REFRIGERATOR_FILE "graphics/Accessories/openFridge.png"
#define USED_BED_FILE "graphics/Accessories/bedSleep.png"

//Pam files
#define HAPPY_PAM_WINDOW "graphics/Pam/happyPam.png"
#define SAD_PAM_WINDOW "graphics/Pam/sadPam.png"
#define SMALL_PAM_WINDOW "graphics/Pam/pamSmall.png"

//Pet folders
#define COCO_FOLDER "graphics/Pet/Fox/"
#define FIFI_FOLDER "graphics/Pet/Penguin/"
#define BOO_FOLDER "graphics/Pet/Pug/"
#define ANGEL_FOLDER "graphics/Pet/Bunny/"

//Effect folders
#define BATH_ANIMATION "graphics/Effects/Water/bath"
#define SLEEP_ANIMATION "graphics/Effects/Sleep/"
#define BEING_PET_ANIMATION "graphics/Effects/Pet/"
#define EGG_GROWING_ANIMATION "graphics/Effects/GrowingEgg/"
#define BABY_GROWING_ANIMATION "graphics/Effects/GrowingBaby/"
//Dark screen file
#define DARK_SCREEN "graphics/Effects/DarkScreen.png"
//Egg select effect file
#define SELECT_EFFECT "graphics/Effects/sparkleChoise.png"

//Toys information
#define FIRST_TOY_EFFECT 8
//Toys animation
#define RIGHT_POST_ANIMATION "graphics/Toys/rightPost.png"
#define LEFT_POST_ANIMATION "graphics/Toys/leftPost.png"
#define SWING_ANIMATION "graphics/Toys/Swing"
#define BALL_ANIMATION "graphics/Toys/Ball"
#define CAR_ANIMATION "graphics/Toys/Car"

//Food animation
#define MILK_ANIMATION "graphics/Food/milk"
#define STRAWBERRY_ANIMATION "graphics/Food/strawberry"
#define BURGER_ANIMATION "graphics/Food/burger"
#define PIZZA_ANIMATION "graphics/Food/pizza"
#define CHOCOLATE_ANIMATION "graphics/Food/chocolate"
#define SALAD_ANIMATION "graphics/Food/salad"

//Menu folders
#define FOOD_MENU "graphics/Buttons/Food/"
#define TOY_MENU "graphics/Buttons/Toys/"

//TicTacToe information
#define ROW_PIECES 3
#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1
#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92
//TicTacToe files
#define X_PIECE_FILEPATH "graphics/Toys/x.png"
#define O_PIECE_FILEPATH "graphics/Toys/o.png"
#define WINNING_PIECE_FILEPATH "graphics/Toys/rightPost.png"
#define LOOSE_PIECE_FILEPATH "graphics/Toys/rightPost.png"
#define GRID_SPRITE_FILEPATH "graphics/Toys/block.png"

enum ActioType {
	STAND = -1,
	PETTED,
	EAT,
	SLEEP,
	SHOWER,
	PLAY,
	GROW,
	TALK,
	INTRO,
	OPEN_REFRIGERATOR,
	OPEN_BOX,
	OTHER_STATE
};

enum MoodType {
	DEAD_MOOD = -1,
	BLACK_MOOD,
	RED_MOOD = 3,
	YELLOW_MOOD = 7,
	GREEAN_MOOD = 10
};