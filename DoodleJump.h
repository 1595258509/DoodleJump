#pragma once
#include "fstream"
#include "map"
#include "thread"
#include "iostream"
#include "Logo.h"
#define _Doodle_Jump_Width_ 500
#define _Doodle_Jump_Height_ 800
#define _land_num_ 10
#define _Gravity_ 0.15
using namespace std;
enum InterfaceType {
	I_welcome, I_rule1, I_rule2, I_rank, I_option, I_change_name, I_gamerun, I_gamepause, I_gameretry, I_gameover
};
enum DJTheme {
	Classic, Jungle, Underwater, Winter
};
enum PlayerStatus {
	p_left, p_right, fly_left1, fly_right1, fly_left2, fly_right2, rocket_left, rocket_right
};
enum LandType {
	normal, fragile, broken, broken_over, mvland, landfly, landrocket, mvspring1, landspring1, mvspring2, landspring2
};
MOUSEMSG msmsg;
KEYMSG kmsg;
struct sortcmp {
	bool operator ()(const int &a, const int &b) const {
		return a > b;
	}
};
class Welcome {
	public:
		IMAGE * im_bk;
		IMAGE * im_bk_bottombar;
		IMAGE * button_start;
		IMAGE * button_continue;
		IMAGE * button_rule;
		IMAGE * button_option;
		IMAGE * button_option_rect;
		IMAGE * button_menu;
		IMAGE * button_rank;
		IMAGE * button_rank_rect;
		IMAGE * button_next;
		IMAGE * button_return;
		IMAGE * button_retry;
		IMAGE * button_on;
		IMAGE * button_off;
		IMAGE * button_pause;
		IMAGE * im_circle;
		IMAGE * im_option;
		IMAGE * im_change_name;
		IMAGE * im_rank;
		IMAGE * im_crown1;
		IMAGE * im_crown2;
		IMAGE * im_crown3;
		IMAGE * im_rule1;
		IMAGE * im_rule2;
		IMAGE * im_topbar;
		IMAGE * im_pauselabel;
		IMAGE * im_you_died;
		IMAGE * im_your_name;
		IMAGE * im_your_score;
		IMAGE * im_highest_score;
		IMAGE * im_gameover;
		InterfaceType interfacetype;
		DJTheme themetype;
		string path, theme, name;
		thread p_mouseget;
		bool bgm, sound_effect;
		multimap<int, string, sortcmp> scorerank_map;
		Welcome();
		void rank_read();//��ȡ����
		void rank_save();//д������
		void change_name();
		void welcome_mouseget();
		void main_interface();//��ʼ����ѭ������
		void draw_welcome();
		void show_rule();//����
		void show_rank(InterfaceType pre);//���а�
		void show_option(InterfaceType pre);//����
		void show_pauselabel();
		void show_gameover();
		void change_theme();
		void draw_jump();//��ʼ��������С��
		void pauseget_mouse();
		void game_run();//��Ϸ����ѭ������
};
class Scene {
	public:
		IMAGE * im_bk;
		IMAGE * im_basicline;
		int direct;
		Scene();
		void change_theme(string theme, string path = "image/Theme/");
		void draw();
		void PlayBGM(string MusicPath = "sounds/bgm.mp3");
		void PlayMusic(string MusicPath);
		void show();
		void updateWithoutInput();
		void updateWithKeyInput();
};
class Land {
	public:
		IMAGE *im_normal; //��������
		IMAGE *im_break; //�������
		IMAGE *im_move; //�ƶ�����
		IMAGE *im_broken; //�𻵵���
		IMAGE *im_landfly; //�����ѵذ�
		IMAGE *im_landrocket; //����ذ�
		IMAGE *im_landspring1; //���е��ɵ���������
		IMAGE *im_landspring2; //���ɱ��ȵ�����������
		IMAGE *im_mvspring1; //���е��ɵ��ƶ�����
		IMAGE *im_mvspring2; //���ɱ��ȵ����ƶ�����
		float land_width, land_height, land_vy;
		int score;
		int broken_y; //��¼����ذ��y����
		struct LandState {
			float middle_x;
			float top_y;
			float vx;
			LandType landType;
			IMAGE *im_land;
		} land[_land_num_];

		Land(string path = "image/Land/");
		void retry_clean();
		void Land_type(int i, int lnor, int lfr, int mv, int lspr, int lfly, int mvspr, int lroc);//������ɵذ�
		void draw();
		void show_topbar();
		void updateLandY();//���µذ�
};
class Player {
	public:
		IMAGE *im_show;
		IMAGE *im_left;
		IMAGE *im_right;
		IMAGE *im_fly_left1;
		IMAGE *im_fly_left2;
		IMAGE *im_fly_right1;
		IMAGE *im_fly_right2;
		IMAGE *im_rocket_left;
		IMAGE *im_rocket_right;
		PlayerStatus playerStatus;
		float x_middle, y_bottom;
		float vx, vy;
		float width, height;
		float rebound_vy;
		bool isPlayer_yMax, isPlayer_died;
		Player(string path = "image/Theme/", string theme = "Classic");
		void retry_clean();
		void change_theme(string theme, string path = "image/Theme/");
		void draw();
		void moveLeft();
		void moveRight();
		void autoJump();
		void autoJump_fly();
		void autoJump_rocket();
		void JudgeisPlayer_yMax();
		void isOnLand();
		void updateYcoordinate();
		void JudgeisPlayer_died();
};
class SaveData {
	public:
		void game_save(); //��Ϸ�浵
		bool game_load(); //��Ϸ����
};
Welcome welcome;
Scene scene;
Land land;
Player player;
SaveData savedata;
