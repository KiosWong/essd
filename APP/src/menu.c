#include "app.h"

static void menu_constructor_functions_1_static(void);
static void menu_constructor_functions_2_static(void);
static void menu_constructor_functions_3_static(void);
static void menu_constructor_functions_4_static(void);

static void menu_constructor_gesture_static(void);

static void menu_constructor_transfer_1_static(void);
static void menu_constructor_transfer_2_static(void);

static void menu_constructor_dual_static(void);

static void menu_constructor_remote_1_static(void);
static void menu_constructor_remote_2_static(void);

static void menu_constructor_functions_1_dynamic(void);
static void menu_constructor_functions_2_dynamic(void);
static void menu_constructor_functions_3_dynamic(void);
static void menu_constructor_functions_4_dynamic(void);

static void menu_constructor_gesture_dynamic(void);

static void menu_constructor_transfer_1_dynamic(void);
static void menu_constructor_transfer_2_dynamic(void);

static void menu_constructor_dual_dynamic(void);

static void menu_constructor_remote_1_dynamic(void);
static void menu_constructor_remote_2_dynamic(void);

extern long timestamp;

menu_t menu;
app_status_t app = {
	{led_off, led_off, led_off, led_off},
	9,
	0,
	10,
};

void (*menu_constructors_static[5][4])() = {
	{menu_constructor_functions_1_static, 	menu_constructor_functions_2_static, 	menu_constructor_functions_3_static, 	menu_constructor_functions_4_static	},
	{menu_constructor_gesture_static, 	NULL, 					NULL, 					NULL					},
	{menu_constructor_transfer_1_static,	menu_constructor_transfer_2_static,	NULL,					NULL					},
	{menu_constructor_dual_static, 		NULL, 					NULL, 					NULL					},
	{menu_constructor_remote_1_static, 	menu_constructor_remote_2_static,	NULL, 					NULL					}
};

void (*menu_constructors_dynamic[5][4])() = {
	{menu_constructor_functions_1_dynamic, 	menu_constructor_functions_2_dynamic, 	menu_constructor_functions_3_dynamic, 	menu_constructor_functions_4_dynamic	},
	{menu_constructor_gesture_dynamic, 	NULL, 					NULL, 					NULL					},
	{menu_constructor_transfer_1_dynamic,	menu_constructor_transfer_2_dynamic,	NULL,					NULL					},
	{menu_constructor_dual_dynamic, 		NULL, 					NULL, 					NULL					},
	{menu_constructor_remote_1_dynamic, 	menu_constructor_remote_2_dynamic,	NULL, 					NULL					}
};

void menu_init()
{
	menu.present_constructor_static = menu_constructors_static[0][0];
	menu.page_index = 0;
	menu.sub_page_index = 0;
	menu.flagIsMainMenu = 1;
	GUI_DispStringHCenterAt("数字系统综合设计", (GUI_GetXSize() + 0) / 2, 16);
	GUI_DispStringHCenterAt("王超 16041531", (GUI_GetXSize() + 0) / 2, 32);
	GUI_DispStringHCenterAt("Advisor: 曾毓", (GUI_GetXSize() + 0) / 2, 48);
	GUI_Update();
	Led_Startup_1();
	GUI_Clear();
	GUI_DrawBitmap(&bmhdulogo, (GUI_GetXSize() - bmhdulogo.XSize) / 2, (GUI_GetYSize() - bmhdulogo.YSize) / 2);
	GUI_Update();
	Led_Startup_2();
}

void menu_constructor_main_static()
{
	uint8_t disp_buffer[20];
	
	GUI_Clear();
	
	GUI_DispStringAt("电子系统综合课程设计", 2, 2);
	
	if(menu.page_index < 3) {
		GUI_DispStringAt("→", 10, 20 + menu.page_index * 14);
		GUI_DispStringAt("1.系统测试", 25, 20);
		GUI_DispStringAt("2.姿态解算", 25, 34);
		GUI_DispStringAt("3.数据传输", 25, 48);
		GUI_DispStringAt("1/2", 106, 50);
	}
	else if(menu.page_index < 5) {
		GUI_DispStringAt("→", 10, 20 + (menu.page_index - 3) * 14);
		GUI_DispStringAt("4.双机通信", 25, 20);
		GUI_DispStringAt("5.远程控制", 25, 34);
		GUI_DispStringAt("2/2", 106, 50);
	}
	
}

static void menu_constructor_functions_1_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("系统测试", 2, 2);
	GUI_DispStringAt("1/4", 108, 2);
	
	GUI_DispStringAt("LED状态:", 8, 21);
	GUI_DispStringAt("按键状态:", 8, 39);
}

static void menu_constructor_functions_2_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("系统测试", 2, 2);
	GUI_DispStringAt("2/4", 108, 2);
	
	GUI_DispStringAt("AD数据", 8, 21);
	GUI_DispStringAt("电压数据:", 72, 21);
}

static void menu_constructor_functions_3_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("系统测试", 2, 2);
	GUI_DispStringAt("3/4", 108, 2);
	
	GUI_DispStringAt("AccX", 14, 16);
	GUI_DispStringAt("AccY", 49, 16);
	GUI_DispStringAt("AccZ", 90, 16);
}

static void menu_constructor_functions_4_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("系统测试", 2, 2);
	GUI_DispStringAt("4/4", 108, 2);
	
	GUI_DispStringAt("GyroX", 10, 16);
	GUI_DispStringAt("GyroY", 52, 16);
	GUI_DispStringAt("GyroZ", 86, 16);
}

static void menu_constructor_gesture_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("姿态解算", 2, 2);
	GUI_DispStringAt("1/1", 108, 2);
	
	GUI_DispStringAt("Pitch:", 8, 21);
	GUI_DispStringAt("Roll:", 8, 34);
	GUI_DispStringAt("Yaw:", 8, 47);
}

static void menu_constructor_transfer_1_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("数据传输", 2, 2);
	GUI_DispStringAt("1/2", 108, 2);
	
	GUI_DispStringAt("帧格式:", 8, 20);
	GUI_DispStringAt("发送间隔:", 8, 34);
	GUI_DispStringAt("发送计数:", 8, 48);
}

static void menu_constructor_transfer_2_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("数据传输", 2, 2);
	GUI_DispStringAt("2/2", 108, 2);
	
	GUI_DispStringAt("接收计数:", 8, 20);
	GUI_DispStringAt("指令类型:", 8, 34);
	GUI_DispStringAt("指令来源:", 8, 48);
}

static void menu_constructor_dual_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("双机通信", 2, 2);
	GUI_DispStringAt("1/1", 108, 2);
	
	GUI_DispStringAt("1.模式切换:", 19, 20);
	GUI_DispStringAt("2.匹配设备:", 19, 34);
	GUI_DispStringAt("3.握手次数:", 19, 48);
}

static void menu_constructor_remote_1_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("远程控制", 2, 2);
	GUI_DispStringAt("1/2", 108, 2);
	
	GUI_DispStringAt("远程开关:", 8, 20);
	GUI_DispStringAt("连接时长:", 8, 34);
}

static void menu_constructor_remote_2_static()
{
	GUI_Clear();
	
	GUI_DispStringAt("远程控制", 2, 2);
	GUI_DispStringAt("2/2", 108, 2);
}

static void menu_constructor_main_dynamic()
{
	uint8_t disp_buffer[20];
	
	GUI_Clear();
	
	GUI_DispStringAt("数字系统课程设计", 2, 2);
	
	if(menu.page_index < 3) {
		GUI_DispStringAt("→", 10, 20 + menu.page_index * 14);
		GUI_DispStringAt("1.系统测试", 25, 20);
		GUI_DispStringAt("2.姿态解算", 25, 34);
		GUI_DispStringAt("3.数据传输", 25, 48);
		GUI_DispStringAt("1/2", 106, 50);
	}
	else if(menu.page_index < 5) {
		GUI_DispStringAt("→", 10, 20 + (menu.page_index - 3) * 14);
		GUI_DispStringAt("4.双机通信", 25, 20);
		GUI_DispStringAt("5.远程控制", 25, 34);
		GUI_DispStringAt("2/2", 106, 50);
	}
	
}

static void menu_constructor_functions_1_dynamic()
{
	char disp_buffer[20];
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%s%s%s%s", ((LED1 == 0) ? "○" : "●"), ((LED2 == 0) ? "○" : "●"), ((LED3 == 0) ? "○" : "●"), ((LED4 == 0) ? "○" : "●"));
	GUI_DispStringAt(disp_buffer, 68, 21);
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%s%s%s%s", ((KEY1 == 0) ? "▂" : "▉"), ((KEY2 == 0) ? "▂" : "▉"), ((KEY3 == 0) ? "▂" : "▉"), ((KEY4 == 0) ? "▂" : "▉"));
	GUI_DispStringAt(disp_buffer, 68, 39);
}

static void menu_constructor_functions_2_dynamic()
{
	uint16_t column_height = 0;
	char disp_buffer[20];
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%d", app.ad_value);
	GUI_DispStringAt(disp_buffer, 12, 39);
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%.2f", (app.ad_value / 4096.0) * 3.3);
	GUI_DispStringAt(disp_buffer, 80, 39);
	
	GUI_ClearRect(49, 24, 20, 24);
	column_height = (uint16_t)(((app.ad_value / 4096.0) * 120) / 5);
	GUI_FillRect(49, 48 - column_height, 68, 48);

}

static void menu_constructor_functions_3_dynamic()
{
	uint16_t column_height = 0;
	char disp_buffer[20];
	
	GUI_ClearRect(0, 51, 128, 12);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%5d", ax);
	GUI_DispStringAt(disp_buffer, 10, 51);
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%5d", ay);
	GUI_DispStringAt(disp_buffer, 52, 51);
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%5d", az);
	GUI_DispStringAt(disp_buffer, 86, 51);
	
	GUI_ClearRect(17, 30, 18, 20);
	column_height = (uint16_t)((((ax + 32767) / 65535.0) * 100) / 5);
	GUI_FillRect(17, 50 - column_height, 17 + 18, 50);
	
	GUI_ClearRect(55, 30, 18, 20);
	column_height = (uint16_t)((((ay + 32767) / 65535.0) * 100) / 5);
	GUI_FillRect(55, 50 - column_height, 55 + 18, 50);
	
	GUI_ClearRect(93, 30, 18, 20);
	column_height = (uint16_t)((((az + 32767) / 65535.0) * 100) / 5);
	GUI_FillRect(93, 50 - column_height, 93 + 18, 50);
	
}

static void menu_constructor_functions_4_dynamic()
{
	int16_t column_height = 0;
	char disp_buffer[20];
	
	GUI_ClearRect(0, 51, 128, 12);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%5d", gx);
	GUI_DispStringAt(disp_buffer, 10, 51);
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%5d", gy);
	GUI_DispStringAt(disp_buffer, 52, 51);
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%5d", gz);
	GUI_DispStringAt(disp_buffer, 86, 51);
	
	GUI_ClearRect(17, 30, 18, 20);
	column_height = (uint16_t)((((gx + 32767) / 65535.0) * 100) / 5);
	GUI_FillRect(17, 50 - column_height, 17 + 18, 50);
	
	GUI_ClearRect(55, 30, 18, 20);
	column_height = (uint16_t)((((gy + 32767) / 65535.0) * 100) / 5);
	GUI_FillRect(55, 50 - column_height, 55 + 18, 50);
	
	GUI_ClearRect(93, 30, 18, 20);
	column_height = (uint16_t)((((gz + 32767) / 65535.0) * 100) / 5);
	GUI_FillRect(93, 50 - column_height, 93 + 18, 50);
}

static void menu_constructor_gesture_dynamic()
{
	char disp_buffer[20];
	
	GUI_ClearRect(58, 21, 70, 12);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%.2f°", fAX);
	GUI_DispStringAt(disp_buffer, 58, 21);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%d%%", (int)(((fAX + 180) / 360) * 100));
	GUI_DispStringAt(disp_buffer, 110, 21);
	
	GUI_ClearRect(58, 34, 70, 12);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%.2f°", fAY);
	GUI_DispStringAt(disp_buffer, 58, 34);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%d%%", (int)(((fAY + 180) / 360) * 100));
	GUI_DispStringAt(disp_buffer, 110, 34);
	
	GUI_ClearRect(58, 47, 70, 12);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%.2f°", fAZ);
	GUI_DispStringAt(disp_buffer, 58, 47);
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%d%%", (int)(((fAZ + 180) / 360) * 100));
	GUI_DispStringAt(disp_buffer, 110, 47);
}

static void menu_constructor_transfer_1_dynamic()
{
	char disp_buffer[20];
	
	memset(disp_buffer, 0, 20);
	switch(app.present_upload_frame) {
		case 0 :
			sprintf(disp_buffer, "7MBD+数据+\\n");
		break;
		
		case 1 :
			sprintf(disp_buffer, "7MY+数据+\\n");
		break;
		
		case 2 :
			sprintf(disp_buffer, "7MR+数据+\\n");
		break;
		
		default : 
			break;
	}
	GUI_ClearRect(50, 20, 78, 12);
	GUI_DispStringAt(disp_buffer, 50, 20);	
	
	memset(disp_buffer, 0, 20);
	if(app.present_upload_interval == 0)
		sprintf(disp_buffer, "@inf");
	else
		sprintf(disp_buffer, "%.2f", app.present_upload_interval / 1000.0);
	GUI_ClearRect(64, 34, 64, 12);
	GUI_DispStringAt(disp_buffer, 64, 34);

	memset(disp_buffer, 0, 20);	
	sprintf(disp_buffer, "%d", app.upload_count);
	GUI_ClearRect(64, 48, 64, 12);
	GUI_DispStringAt(disp_buffer, 64, 48);
}

static void menu_constructor_transfer_2_dynamic()
{
	
	char disp_buffer[20];
	
	memset(disp_buffer, 0, 20);
	sprintf(disp_buffer, "%d", app.recev_count);
	GUI_ClearRect(64, 20, 78, 12);
	GUI_DispStringAt(disp_buffer, 64, 20);
	
	memset(disp_buffer, 0, 20);
	switch(app.present_recev_type) {
		case 0 :
			sprintf(disp_buffer, "NULL");
		break;
		
		case 1 :
			sprintf(disp_buffer, "亮灭控制");
		break;
		
		case 2 :
			sprintf(disp_buffer, "动态控制");
		break;
		
		case 3 :
			sprintf(disp_buffer, "调光控制");
		break;
		
		case 4 :
			sprintf(disp_buffer, "上传控制");
		break;
		
		default : 
			break;
	}
	GUI_ClearRect(64, 34, 64, 12);
	GUI_DispStringAt(disp_buffer, 64, 34);
	
	switch(app.present_recev_source) {
		case 0 :
			sprintf(disp_buffer, "NULL");
		break;
		
		case 1 :
			sprintf(disp_buffer, "上位机");
		break;
		
		case 2 :
			sprintf(disp_buffer, "APP");
		break;
		
		default : 
			break;
	}
	GUI_ClearRect(64, 48, 64, 12);
	GUI_DispStringAt(disp_buffer, 64, 48);
	
}

static void menu_constructor_dual_dynamic()
{
	char disp_buffer[20];
	
	memset(disp_buffer, 0, 20);
	if(app.pre_dual_mode == 0) {
		if(app.dual_mode == 0)
			sprintf(disp_buffer, "关 √");
		else
			sprintf(disp_buffer, "关 ×");
	}
	else if(app.pre_dual_mode == 1) {
		if(app.dual_mode == 1)
			sprintf(disp_buffer, "从 √");
		else
			sprintf(disp_buffer, "从 ×");
	}
	else if(app.pre_dual_mode == 2) {
		if(app.dual_mode == 2)
			sprintf(disp_buffer, "主 √");
		else
			sprintf(disp_buffer, "主 ×");
	}
	GUI_ClearRect(90, 20, 38, 12);
	GUI_DispStringAt(disp_buffer, 90, 20);
	
	memset(disp_buffer, 0, 20);
	if(app.dual_name[0] != 0)
		sprintf(disp_buffer, "%s", app.dual_name);
	else
		sprintf(disp_buffer, "NULL");
	GUI_ClearRect(90, 34, 38, 12);
	GUI_DispStringAt(disp_buffer, 90, 34);
	
	memset(disp_buffer, 0, 20);
	if(app.dual_mode != 0)
		sprintf(disp_buffer, "%d", app.handshake_count);
	else
		sprintf(disp_buffer, "NULL");
	GUI_ClearRect(90, 48, 38, 12);
	GUI_DispStringAt(disp_buffer, 90, 48);
}

static void menu_constructor_remote_1_dynamic()
{ 
	char disp_buffer[20];
	
	memset(disp_buffer, 0, 20);
	if(app.remote_switch == 0)
		sprintf(disp_buffer, "关");
	if(app.remote_switch == 1)
		sprintf(disp_buffer, "开");
	GUI_ClearRect(65, 20, 63, 12);
	GUI_DispStringAt(disp_buffer, 65, 20);
	
	
	memset(disp_buffer, 0, 20);
	if(app.remote_switch && STATE == 1)
		sprintf(disp_buffer, "%d:%d:%d", app.remote_second / 3600, (app.remote_second % 3600) / 60, app.remote_second % 60);
	else {
		sprintf(disp_buffer, "NULL");
		app.remote_second = 0;
	}
	GUI_DispStringAt(disp_buffer, 65, 34);
}

static void menu_constructor_remote_2_dynamic()
{
	GUI_ClearRect(app.remote_x_ex, app.remote_y_ex + 16, 15, 15);
	GUI_FillRect(app.remote_x_now, app.remote_y_now + 16, app.remote_x_now + 15, app.remote_y_now + 16 + 15);
	app.remote_x_ex = app.remote_x_now;
	app.remote_y_ex = app.remote_y_now;
}




