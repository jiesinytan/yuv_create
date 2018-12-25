/*created by Jinwei Liu */
#include <math.h>
#include <stdlib.h>
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

int main(int argc, char **argv)
{
	AVFrame *frame;
	char *p;
	int i,x,y;
	/* register all the codecs */
	av_register_all();
	if(argc!=3)
		printf("usage:./encodec.bin widht height\n");
	frame = av_frame_alloc();
	frame->width = atoi(argv[1]);
	frame->height = atoi(argv[2]);
	av_image_alloc(frame->data,frame->linesize,frame->width,frame->height,AV_PIX_FMT_YUV420P,32);
	FILE * file_fd =fopen("soft.yuv","wb+");
	for (i = 0; i < 200; i++) {
		/* prepare a dummy image */ /* Y */
		for (y = 0; y < frame->height; y++) {
			for (x = 0; x < frame->width; x++) {
				frame->data[0][y * frame->width + x] = (x + y + i * 3)%255;
			}
		}
		/* Cb and Cr */
		for (y = 0; y < frame->height/2; y++) {
			for (x = 0; x < frame->width/2; x++) {
				frame->data[1][y * frame->width / 2 + x] = (y + y + i * 2)%255;
				frame->data[2][y * frame->width / 2 + x] = (x + x + i * 5)%255;
			}
		}
		fwrite(frame->data[0],1,frame->width*frame->height,file_fd);
		fwrite(frame->data[1],1,frame->width*frame->height/4,file_fd);
		fwrite(frame->data[2],1,frame->width*frame->height/4,file_fd);
	}
	fclose(file_fd);
	av_freep(frame->data);
	av_free(frame);
	return 0;
}
