
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nidcompat.h"



size_t nidcompat_memory_usage_rate = 0;

size_t nidcompat_get_memory_usage_rate(void){
	return nidcompat_memory_usage_rate;
}

void *nidcompat_malloc(size_t size){

	size_t extend_size = (size + sizeof(size_t));

	void *ptr = malloc(extend_size);
	if(ptr != NULL){
		nidcompat_memory_usage_rate += size;
		*(size_t *)(ptr) = size;
		ptr += sizeof(size_t);
	}

	return ptr;
}

void nidcompat_free(void *ptr){

	if(ptr != NULL){
		ptr -= sizeof(size_t);
		nidcompat_memory_usage_rate -= *(size_t *)(ptr);
	}

	return free(ptr);
}


int name_copyin(const char *name, char **result){

	int name_len = strlen(name);

	char *new_name = nidcompat_malloc(name_len + 1);

	new_name[name_len] = 0;
	memcpy(new_name, name, name_len);

	*result = new_name;

	return 0;
}

int is_number_ch(int ch){
	if((unsigned)(ch - '0') <= 9){
		return 1;
	}

	return 0;
}

int parse_fw_string(const char *s, uint32_t *v){

	if(strlen(s) > strlen("00.000.000")){
		printf("error %d\n", __LINE__);
		return -1;
	}

	if(s[0] == '.'){
		printf("error %d\n", __LINE__);
		return -1;
	}

	char fws[0x10];

	if(s[1] == '.'){
		snprintf(fws, sizeof(fws), "0%s", s);
	}else{
		snprintf(fws, sizeof(fws), "%s", s);
	}

	if(strlen(fws) == strlen("00.00")){
		snprintf(&(fws[5]), 8, "0.000");
	}else if(strlen(fws) == strlen("00.000")){
		snprintf(&(fws[6]), 8, ".000");
	}else if(strlen(fws) == strlen("00.000.000")){
	}

	if(fws[2] != '.'){return -1;}
	if(fws[6] != '.'){return -1;}

	// .
	fws[2] = fws[3];
	fws[3] = fws[4];
	fws[4] = fws[5];
	// .
	fws[5] = fws[7];
	fws[6] = fws[8];
	fws[7] = fws[9];
	fws[8] = 0;

	if(is_number_ch(fws[0]) == 0){return -1;}
	if(is_number_ch(fws[1]) == 0){return -1;}
	if(is_number_ch(fws[2]) == 0){return -1;}
	if(is_number_ch(fws[3]) == 0){return -1;}
	if(is_number_ch(fws[4]) == 0){return -1;}
	if(is_number_ch(fws[5]) == 0){return -1;}
	if(is_number_ch(fws[6]) == 0){return -1;}
	if(is_number_ch(fws[7]) == 0){return -1;}

	*v = strtol(fws, NULL, 16);

	return 0;
}

int parse_fw_range_string(const char *s, uint32_t *from, uint32_t *to){

	char fw_str[0x20];

	if(strlen(s) > strlen("00.000.000-99.999.999")){
		printf("error %d\n", __LINE__);
		return -1;
	}

	snprintf(fw_str, sizeof(fw_str), "%s", s);

	char *to_s = strchr(fw_str, '-');
	if(to_s != NULL){

		*to_s = 0;

		parse_fw_string(fw_str, from);
		parse_fw_string(&(to_s[1]), to);
	}else{
		parse_fw_string(fw_str, from);
		parse_fw_string(fw_str, to);
	}

	return 0;
}

int read_file(const char *path, void **data, size_t *read_size){

	int res;
	FILE *fd;

	fd = fopen(path, "rb");
	if(fd == NULL){
		printf("Failed open to %s\n", path);
		return -1;
	}

	fseek(fd, 0, SEEK_END);
	off_t file_size = ftell(fd);

	void *data_buffer = nidcompat_malloc(file_size);

	fseek(fd, 0, SEEK_SET);

	res = fread(data_buffer, 1, file_size, fd);
	if(res < 0){
		nidcompat_free(data_buffer);
		data_buffer = NULL;
	}

	fclose(fd);
	fd = NULL;

	if(data_buffer == NULL){
		return -1;
	}

	if(data != NULL){
		*data = data_buffer;
	}else{
		nidcompat_free(data_buffer);
		data_buffer = NULL;
	}

	if(read_size != NULL){
		*read_size = file_size;
	}

	return 0;
}

int read_text_file(const char *path, char **data, size_t *read_size){

	int res;
	FILE *fd;

	fd = fopen(path, "rb");
	if(fd == NULL){
		printf("Failed open to %s\n", path);
		return -1;
	}

	fseek(fd, 0, SEEK_END);
	off_t txt_size = ftell(fd);

	char *txt = nidcompat_malloc(txt_size + 1);
	txt[txt_size] = 0;

	fseek(fd, 0, SEEK_SET);

	res = fread(txt, 1, txt_size, fd);
	if(res < 0){
		nidcompat_free(txt);
		txt = NULL;
	}

	fclose(fd);
	fd = NULL;

	if(txt == NULL){
		return -1;
	}

	if(data != NULL){
		*data = txt;
	}else{
		nidcompat_free(txt);
		txt = NULL;
	}

	if(read_size != NULL){
		*read_size = txt_size;
	}

	return 0;
}
