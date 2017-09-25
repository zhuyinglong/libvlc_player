#include <iostream>
#include <windows.h>
#include "configs.h"
using namespace std;
/**
 *本程序是根据雷神最简单的基于libVLC的视频播放器改写。
 *仅供学习使用。
 *编译平台WIN32
 */
int main()
{
	libvlc_instance_t * inst = 0;
	libvlc_media_player_t *mp = 0;
	libvlc_media_t *m = 0;

	libvlc_time_t length = 0;
	int width = 0;
	int height = 0;
	int wait_time = 5000;

	/* Load the VLC engine */
	inst = libvlc_new(0, NULL);

	//Create a new item
	//播放网络地址。参数内容为自己在本地搭建的点播的rtmp服务器点播地址，大家在调试程序时可以改为其他可用的网络播放地址。
	//m = libvlc_media_new_location (inst, "rtmp://192.168.154.203:1935/vod/sample.mp4");
	//播放本地视频文件。test.mp4存放在cpp文件所在的目录。
	m = libvlc_media_new_path(inst, "test.mp4");

	/**
	 *显示屏幕内容。
	 *因为要显示的内容包括播放窗口，若播放窗口显示在桌面上，播放器会不停嵌套显示。大家可以尝试看下效果。
	 */
	//m = libvlc_media_new_location (inst, "screen://");

	/* Create a media player playing environement */
	mp = libvlc_media_player_new_from_media(m);

	/* No need to keep the media now */
	libvlc_media_release(m);
	// play the media_player
	libvlc_media_player_play(mp);
	//wait until the tracks are created；在播放wait_time之后显示以下三个内容。
	Sleep(wait_time);
	length = libvlc_media_player_get_length(mp);
	width = libvlc_video_get_width(mp);
	height = libvlc_video_get_height(mp);
	cout << "Stream Duration:" << length / 1000 <<endl;
	cout << "Resolution:" << width << "*" << height << endl;
	//等待（总时长-wait_time），这样可以保证视频刚好播放到结尾。
	Sleep((DWORD)(length - wait_time));

	// Stop playing
	libvlc_media_player_stop(mp);

	// Free the media_player
	libvlc_media_player_release(mp);

	libvlc_release(inst);
	return 0;
}