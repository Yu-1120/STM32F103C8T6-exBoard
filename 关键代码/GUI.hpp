#ifndef __GUI_HPP__
#define __GUI_HPP__

#define BetUiDis    60


//Icon_Par
struct Icon_Par {
	int Targrt_x;
	int Targrt_y;
	float Out_x;
	float Out_y;

} ;
//Menu_t
struct Menu_t{
	
	//icon
	struct Icon_Par Icon_R2;
	struct Icon_Par Icon_R1;
	struct Icon_Par Icon_0;
	struct Icon_Par Icon_L1;
	struct Icon_Par Icon_L2;
	//font
	struct Icon_Par Font_0;
	struct Icon_Par Font_L1;
	struct Icon_Par Font_R1;
};
struct SetPoint_t
{
	int Targrt_x;
	int Targrt_y;
	int Targrt_len;
	float Out_x;
	float Out_y;
	float Out_len;//白色快的长度
	
	int LisTarget_x;
	int LisTarget_y;
	float Out_Lisx;
	float Out_Lisy;
	
	int LisTarget_x2;
	float Out_Lisx2;
	int LisTarget_x3;
	float Out_Lisx3;
};
	
void GUI_Task(void *param);

#endif
