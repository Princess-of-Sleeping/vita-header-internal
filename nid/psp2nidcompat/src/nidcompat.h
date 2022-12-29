
#ifndef _NIDCOMPAT_H_
#define _NIDCOMPAT_H_


#include <string.h>
#include <stdio.h>
#include <stdint.h>


typedef uint32_t SceUIntPtr;
typedef uint32_t SceUInt32;
typedef uint16_t SceUInt16;
typedef uint8_t SceUInt8;

typedef struct SceModuleEntryPoint { // size is 0x5C-bytes
	SceUInt16 attr;
	SceUInt8 minor;
	SceUInt8 major;
	char name[27];
	SceUInt8 type;
	SceUInt32 gp_value;
	SceUIntPtr libent_top;
	SceUIntPtr libent_btm;
	SceUIntPtr libstub_top;
	SceUIntPtr libstub_btm;
	SceUInt32 fingerpint;
	int unk_0x38;
	int unk_0x3C;
	int unk_0x40;
	SceUInt32 module_start;
	SceUInt32 module_stop;
	SceUIntPtr exidx_start;
	SceUIntPtr exidx_end;
	SceUIntPtr extab_start;
	SceUIntPtr extab_end;
} SceModuleEntryPoint;

typedef struct SceModuleExport { // size is 0x20-bytes
	uint8_t size;
	uint8_t auxattr;
	uint16_t version;
	uint16_t flags; // 0x4000:user export
	uint16_t entry_num_function;
	uint16_t entry_num_variable;
	uint16_t data_0x0A; // unused?
	uint32_t data_0x0C; // unused?
	uint32_t libnid;
	SceUIntPtr libname;
	SceUIntPtr table_nid;
	SceUIntPtr table_entry;
} SceModuleExport;



typedef struct NIDCompatDBRange {
	struct NIDCompatDBRange *next;
	uint32_t from;
	uint32_t to;
	void *argp;
} NIDCompatDBRange;

typedef struct NIDCompatDBRangeCB {
	NIDCompatDBRange *head;
	NIDCompatDBRange *tail;
} NIDCompatDBRangeCB;

typedef struct NIDCompatDBEntry {
	struct NIDCompatDBEntry *next;
	char *name;
	char *comment_wiki;
	NIDCompatDBRangeCB range;
	NIDCompatDBRangeCB define_range;
	NIDCompatDBRangeCB define_comment_range;
} NIDCompatDBEntry;

typedef struct NIDCompatDBEntryCB {
	NIDCompatDBEntry *head;
	NIDCompatDBEntry *tail;
} NIDCompatDBEntryCB;

typedef struct NIDCompatDBLibrary {
	struct NIDCompatDBLibrary *next;
	char *name;
	int is_kernel;
	NIDCompatDBRangeCB range;
	NIDCompatDBEntryCB function;
	NIDCompatDBEntryCB variable;
	NIDCompatDBEntry *last;
} NIDCompatDBLibrary;

typedef struct NIDCompatDBLibraryCB {
	NIDCompatDBLibrary *head;
	NIDCompatDBLibrary *tail;
} NIDCompatDBLibraryCB;

typedef struct NIDCompatDB {
	struct NIDCompatDB *next;
	char *file_name;
	NIDCompatDBRangeCB range; // for library host module
	NIDCompatDBLibraryCB library;
} NIDCompatDB;


int nidcompat_is_available(void);
int nidcompat_insert_new_db(void);
int nidcompat_set_db_file_name(const char *name);

int nidcompat_add_host_module(uint32_t from, uint32_t to, const char *name);
int nidcompat_add_library(const char *name);
int nidcompat_set_library_mode(const char *mode);
int nidcompat_set_library_info(int version, uint32_t libnid, uint32_t from, uint32_t to);

int nidcompat_add_function(const char *name);
int nidcompat_set_function_nid(uint32_t nid, uint32_t from, uint32_t to);
int nidcompat_add_variable(const char *name);
int nidcompat_set_variable_nid(uint32_t nid, uint32_t from, uint32_t to);

int nidcompat_set_define(const char *define, uint32_t from, uint32_t to);
int nidcompat_set_define_comment(const char *comment, uint32_t from, uint32_t to);
int nidcompat_set_comment_wiki(const char *comment);

int nidcompat_free_db(void);

int nidcompat_create_library(uint32_t target_fw, const char *module_name, const char *name, int version, uint32_t libnid);
int nidcompat_update_library_info(uint32_t target_fw, const char *module_name, const char *name, int version, uint32_t libnid, const uint32_t *nidtable, int function_num, int variable_num);
int nidcompat_save_current_db(const char *output_dir);


void *nidcompat_malloc(size_t size);
void nidcompat_free(void *ptr);
size_t nidcompat_get_memory_usage_rate(void);

int name_copyin(const char *name, char **result);
int is_number_ch(int ch);
int parse_fw_string(const char *s, uint32_t *v);
int parse_fw_range_string(const char *s, uint32_t *from, uint32_t *to);

int read_file(const char *path, void **data, size_t *read_size);
int read_text_file(const char *path, char **data, size_t *read_size);


#endif /* _NIDCOMPAT_H_ */
