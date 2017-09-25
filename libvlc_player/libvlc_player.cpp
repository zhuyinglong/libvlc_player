#include <iostream>
#include <windows.h>
#include "configs.h"
using namespace std;
/**
 *�������Ǹ���������򵥵Ļ���libVLC����Ƶ��������д��
 *����ѧϰʹ�á�
 *����ƽ̨WIN32
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
	//���������ַ����������Ϊ�Լ��ڱ��ش�ĵ㲥��rtmp�������㲥��ַ������ڵ��Գ���ʱ���Ը�Ϊ�������õ����粥�ŵ�ַ��
	//m = libvlc_media_new_location (inst, "rtmp://192.168.154.203:1935/vod/sample.mp4");
	//���ű�����Ƶ�ļ���test.mp4�����cpp�ļ����ڵ�Ŀ¼��
	m = libvlc_media_new_path(inst, "test.mp4");

	/**
	 *��ʾ��Ļ���ݡ�
	 *��ΪҪ��ʾ�����ݰ������Ŵ��ڣ������Ŵ�����ʾ�������ϣ��������᲻ͣǶ����ʾ����ҿ��Գ��Կ���Ч����
	 */
	//m = libvlc_media_new_location (inst, "screen://");

	/* Create a media player playing environement */
	mp = libvlc_media_player_new_from_media(m);

	/* No need to keep the media now */
	libvlc_media_release(m);
	// play the media_player
	libvlc_media_player_play(mp);
	//wait until the tracks are created���ڲ���wait_time֮����ʾ�����������ݡ�
	Sleep(wait_time);
	length = libvlc_media_player_get_length(mp);
	width = libvlc_video_get_width(mp);
	height = libvlc_video_get_height(mp);
	cout << "Stream Duration:" << length / 1000 <<endl;
	cout << "Resolution:" << width << "*" << height << endl;
	//�ȴ�����ʱ��-wait_time�����������Ա�֤��Ƶ�պò��ŵ���β��
	Sleep((DWORD)(length - wait_time));

	// Stop playing
	libvlc_media_player_stop(mp);

	// Free the media_player
	libvlc_media_player_release(mp);

	libvlc_release(inst);
	return 0;
}