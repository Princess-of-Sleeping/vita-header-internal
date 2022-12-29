
#include <string.h>
#include <stdio.h>
#include <zlib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include "elf.h"
#include "nidcompat.h"
#include "fs_list.h"



// format: ${ver_range} ${modname}
int nidcompat_module(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	char *s_ptr = strchr(argp, ' ');
	if(s_ptr == NULL){
		printf("arg is too short\n");
		return -1;
	}

	*s_ptr = 0;

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(argp, &from, &to);

	nidcompat_add_host_module(from, to, &(s_ptr[1]));

	return 0;
}

int nidcompat_library(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') != NULL){
		printf("arg is too many\n");
	}

	nidcompat_add_library((const char *)argp);

	return 0;
}

int nidcompat_library_mode(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') != NULL){
		printf("arg is too many\n");
	}

	nidcompat_set_library_mode((const char *)argp);

	return 0;
}

int nidcompat_library_info(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') == NULL){
		printf("arg is too short\n");
		return -1;
	}

	int version = strtol(argp, &argp, 10);

	if(*argp != ' '){
		printf("arg is too short\n");
		return -1;
	}

	uint32_t nid = strtol(&(argp[1]), &argp, 16);

	char *fw_range = &(argp[1]);

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(fw_range, &from, &to);

	nidcompat_set_library_info(version, nid, from, to);

	return 0;
}

int nidcompat_function(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') != NULL){
		printf("arg is too many\n");
		return -1;
	}

	nidcompat_add_function((const char *)argp);

	return 0;
}

int nidcompat_function_nid(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') == NULL){
		printf("arg is too short\n");
		return -1;
	}

	uint32_t nid = strtol(argp, &argp, 16);

	char *fw_range = &(argp[1]);

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(fw_range, &from, &to);

	nidcompat_set_function_nid(nid, from, to);

	return 0;
}

int nidcompat_variable(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') != NULL){
		printf("arg is too many\n");
		return -1;
	}

	nidcompat_add_variable((const char *)argp);

	return 0;
}

// format: ${nid} ${versrion_range}
int nidcompat_variable_nid(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') == NULL){
		printf("arg is too short\n");
		return -1;
	}

	uint32_t nid = strtol(argp, &argp, 16);

	char *fw_range = &(argp[1]);

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(fw_range, &from, &to);

	nidcompat_set_variable_nid(nid, from, to);

	return 0;
}

int nidcompat_define(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') == NULL){
		printf("arg is too short\n");
		return -1;
	}

	char *define = strchr(argp, ' ');

	*define = 0;

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(argp, &from, &to);

	nidcompat_set_define(&(define[1]), from, to);

	return 0;
}

int nidcompat_define_dev(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') == NULL){
		printf("arg is too short\n");
		return -1;
	}

	char *define = strchr(argp, ' ');

	*define = 0;

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(argp, &from, &to);

	// TODO
	printf("\tDEFINE_DEV: 0x%X-0x%X %s\n", from, to, &(define[1]));

	// nidcompat_set_define_dev(&(define[1]), from, to);

	return 0;
}

int nidcompat_define_comment(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	if(strchr(argp, ' ') == NULL){
		printf("arg is too short\n");
		return -1;
	}

	char *define = strchr(argp, ' ');

	*define = 0;

	uint32_t from = 0xDEADBEEF;
	uint32_t to = 0xDEADBEEF;

	parse_fw_range_string(argp, &from, &to);

	nidcompat_set_define_comment(&(define[1]), from, to);

	return 0;
}

int nidcompat_comment_wiki(char *argp){

	if(argp == NULL || nidcompat_is_available() == 0){
		return -1;
	}

	nidcompat_set_comment_wiki((char *)argp);

	return 0;
}

typedef struct NIDCompatParseCallback {
	const char *cmdname;
	int (* f)(char *s);
} NIDCompatParseCallback;

const NIDCompatParseCallback nidcompat_callback_list[] = {
	{
		.cmdname = "MODULE:",
		.f = nidcompat_module
	},
	{
		.cmdname = "LIBRARY:",
		.f = nidcompat_library
	},
	{
		.cmdname = "LIBRARY_INFO:",
		.f = nidcompat_library_info
	},
	{
		.cmdname = "LIBRARY_MODE:",
		.f = nidcompat_library_mode
	},
	{
		.cmdname = "FUNCTION:",
		.f = nidcompat_function
	},
	{
		.cmdname = "FUNCTION_NID:",
		.f = nidcompat_function_nid
	},
	{
		.cmdname = "VARIABLE:",
		.f = nidcompat_variable
	},
	{
		.cmdname = "VARIABLE_NID:",
		.f = nidcompat_variable_nid
	},
	{
		.cmdname = "DEFINE:",
		.f = nidcompat_define
	},
	{
		.cmdname = "DEFINE_DEV:",
		.f = nidcompat_define_dev
	},
	{
		.cmdname = "DEFINE_COMMENT:",
		.f = nidcompat_define_comment
	},
	{
		.cmdname = "COMMENT_WIKI:",
		.f = nidcompat_comment_wiki
	}
};

#define nidcompat_callback_list_number (sizeof(nidcompat_callback_list) / sizeof(nidcompat_callback_list[0]))

int nidcompat_parse(const char *txt, int length){
	// printf("%s\n", txt);

	int res, ch, ignore_line, current_line;

	current_line = 1;
	ignore_line = 0;

	do {
		ch = *txt;
		if(ch == 0){
		}else if(ch == '\t' || ch == ' '){
			txt++;
		}else if(ch == '\n'){
			txt++;
			ignore_line = 0;
			current_line++;
		}else if(ignore_line != 0){
			txt++;
		}else if(ch == '#'){ // is comment
			ignore_line = 1;
		}else{

			for(int i=0;i<nidcompat_callback_list_number;i++){

				const char *cmdname = nidcompat_callback_list[i].cmdname;
				int cmdname_len = strlen(cmdname);

				if(strncmp(cmdname, txt, cmdname_len) == 0 && txt[cmdname_len] == ' '){
					ignore_line = 1;
					// printf("Found for %s\n", cmdname);

					const char *txt_ptr = &(txt[cmdname_len + 1]);

					char *s = strchr(txt_ptr, '\n');
					if(s == NULL){
						s = strchr(txt_ptr, 0);
					}

					char *f_arg = nidcompat_malloc((s - txt_ptr) + 1);
					f_arg[s - txt_ptr] = 0;
					memcpy(f_arg, txt_ptr, s - txt_ptr);

					// printf("arg: %s\n", f_arg);

					if(nidcompat_callback_list[i].f != NULL){
						res = nidcompat_callback_list[i].f(f_arg);
					}

					nidcompat_free(f_arg);

					if(res < 0){
						ignore_line = 0;
					}

					break;
				}
			}

			if(ignore_line == 0){
				printf("unk cmd for line %d\n", current_line);
				return -1;
			}
		}
	} while(ch != 0);

	return 0;
}


int nidcompat_db_load_callback(FSListEntry *ent, void *argp){

	if(ent->isDir != 0){
		return 0;
	}

	char *txt = NULL;

	read_text_file(ent->path_full, &txt, NULL);

	if(txt != NULL){
		nidcompat_insert_new_db();
		nidcompat_set_db_file_name(ent->name);
		int res = nidcompat_parse(txt, 0);
		nidcompat_free(txt);
		if(res < 0){
			printf("%s: failed for %s\n", __FUNCTION__, ent->name);
			return -1;
		}
	}

	return 0;
}

int nidcompat_update_db_range_by_elf(uint32_t target_fw, uint32_t va, void *segment, const SceModuleEntryPoint *ep){

	char module_name[0x1C];

	strncpy(module_name, ep->name, 0x1B);
	module_name[0x1B] = 0;


	SceModuleExport *pExport = segment + ep->libent_top;

	while(pExport != (segment + ep->libent_btm)){

		const SceUInt32 *nidtable = segment + (pExport->table_nid - va);
		const SceUIntPtr *enttable = segment + (pExport->table_entry - va);

		if(pExport->libname == 0){

			for(int n=0;n<pExport->entry_num_variable;n++){
				SceUInt32 nid = nidtable[pExport->entry_num_function + n];
				SceUInt32 ent = enttable[pExport->entry_num_function + n];

				SceUIntPtr *pent = segment + (ent - va);

				if(nid == 0x936C8A78){
					target_fw = *pent;
				}
			}
		}
		pExport++;
	}

	printf("[%-27s] 0x%X\n", module_name, target_fw);

	pExport = segment + ep->libent_top;

	while(pExport != (segment + ep->libent_btm)){

		const SceUInt32 *nidtable = segment + (pExport->table_nid - va);
		const SceUIntPtr *enttable = segment + (pExport->table_entry - va);

		if(pExport->libname != 0){
			const char *name = (const char *)(segment + (pExport->libname - va));

			printf("\t%s\n", name);
			nidcompat_update_library_info(target_fw, module_name, name, pExport->version, pExport->libnid, nidtable, pExport->entry_num_function, pExport->entry_num_variable);
		}

		pExport++;
	}

	return 0;
}



typedef struct FWEntry {
	const char *version;
	const char *name;
} FWEntry;

int nidcompat_elf_load_callback(FSListEntry *ent, void *argp){

	const FWEntry *fw_ent = argp;

	if(ent->isDir != 0){
		return 0;
	}

	if(strstr(ent->path_full, ".elf") == NULL && strstr(ent->path_full, ".skprx") == NULL){
		return 0;
	}

	uint32_t fw_version = 0;

	parse_fw_string(fw_ent->version, &fw_version);

	void *elf_data = NULL;
	size_t elf_size = 0;

	read_file(ent->path_full, &elf_data, &elf_size);
	if(elf_data == NULL){
		return 0;
	}

	Elf32_Ehdr *pEhdr = (Elf32_Ehdr *)(elf_data);
	Elf32_Phdr *pPhdr = (Elf32_Phdr *)(elf_data + pEhdr->e_phoff);

	if(strncmp(&(pEhdr->e_ident[1]), "ELF", 3) != 0 || (pEhdr->e_type & 0xFF00) != 0xFE00 || pEhdr->e_machine != EM_ARM || pEhdr->e_entry == 0){
		nidcompat_free(elf_data);
		return 0;
	}

	if(pEhdr->e_entry > elf_size){
		printf("module is broken -> fw 0x%X, file %s (0x%lX-bytes), entry offset 0x%X\n", fw_version, ent->name, elf_size, pEhdr->e_entry);
		nidcompat_free(elf_data);
		return 0;
	}

	for(int i=0;i<pEhdr->e_phnum;i++){
		void *segment = (void *)(elf_data + pPhdr[i].p_offset);

		if(pPhdr[i].p_type == 1 && (pPhdr[i].p_flags & 7) == 5){
			const SceModuleEntryPoint *ep = (const SceModuleEntryPoint *)(segment + pEhdr->e_entry);
			nidcompat_update_db_range_by_elf(fw_version, pPhdr[i].p_vaddr, segment, ep);
		}
	}

	nidcompat_free(elf_data);

	return 0;
}






FWEntry FWEntry_list[] = {
	{
		.version = "3.740.011",
		.name = "../host0/pup_output/Decrypted-PUP/type3/Retail/PSP2UPDAT_3.74.PUP"
	}
};



#define FWEntry_list_number (sizeof(FWEntry_list) / sizeof(FWEntry_list[0]))



int nidcompat_update_all(void){

	int res;
	FSListEntry *pEnt = NULL;

	res = fs_list_init("./db", &pEnt, NULL, NULL);
	if(res >= 0){
		res = fs_list_execute(pEnt->child, nidcompat_db_load_callback, NULL);
	}
	fs_list_fini(pEnt);
	pEnt = NULL;

	printf("nidcompat_memory_usage_rate: 0x%lX\n", nidcompat_get_memory_usage_rate());

	if(res < 0){
		return -1;
	}

	char path[0x400];

	for(int i=0;i<FWEntry_list_number;i++){
		snprintf(path, sizeof(path), "%s", FWEntry_list[i].name);

		res = fs_list_init(path, &pEnt, NULL, NULL);
		if(res >= 0){
			fs_list_execute(pEnt->child, nidcompat_elf_load_callback, &(FWEntry_list[i]));
		}
		fs_list_fini(pEnt);
		pEnt = NULL;
	}

	printf("nidcompat_memory_usage_rate: 0x%lX\n", nidcompat_get_memory_usage_rate());

	nidcompat_save_current_db("./db");

	nidcompat_free_db();

	return 0;
}





int nidcompat_create_db_range_by_elf(uint32_t target_fw, uint32_t va, void *segment, const SceModuleEntryPoint *ep){

	char module_name[0x1C];

	strncpy(module_name, ep->name, 0x1B);
	module_name[0x1B] = 0;


	SceModuleExport *pExport = segment + ep->libent_top;

	while(pExport != (segment + ep->libent_btm)){

		const SceUInt32 *nidtable = segment + (pExport->table_nid - va);
		const SceUIntPtr *enttable = segment + (pExport->table_entry - va);

		if(pExport->libname == 0){

			for(int n=0;n<pExport->entry_num_variable;n++){
				SceUInt32 nid = nidtable[pExport->entry_num_function + n];
				SceUInt32 ent = enttable[pExport->entry_num_function + n];

				SceUIntPtr *pent = segment + (ent - va);

				if(nid == 0x936C8A78){
					target_fw = *pent;
				}
			}
		}
		pExport++;
	}

	printf("[%-27s] 0x%X\n", module_name, target_fw);

	pExport = segment + ep->libent_top;

	while(pExport != (segment + ep->libent_btm)){

		const SceUInt32 *nidtable = segment + (pExport->table_nid - va);
		const SceUIntPtr *enttable = segment + (pExport->table_entry - va);

		if(pExport->libname != 0){
			const char *name = (const char *)(segment + (pExport->libname - va));

			printf("\t%s\n", name);
			nidcompat_create_library(target_fw, module_name, name, pExport->version, pExport->libnid);
		}

		pExport++;
	}

	return 0;
}


int nidcompat_create_callback(FSListEntry *ent, void *argp){

	const FWEntry *fw_ent = argp;

	if(ent->isDir != 0){
		return 0;
	}

	if(strstr(ent->path_full, ".elf") == NULL){
		return 0;
	}

	uint32_t fw_version = 0;

	parse_fw_string(fw_ent->version, &fw_version);

	void *elf_data = NULL;
	size_t elf_size = 0;

	read_file(ent->path_full, &elf_data, &elf_size);
	if(elf_data == NULL){
		return 0;
	}

	Elf32_Ehdr *pEhdr = (Elf32_Ehdr *)(elf_data);
	Elf32_Phdr *pPhdr = (Elf32_Phdr *)(elf_data + pEhdr->e_phoff);

	if(strncmp(&(pEhdr->e_ident[1]), "ELF", 3) != 0 || (pEhdr->e_type & 0xFF00) != 0xFE00 || pEhdr->e_machine != EM_ARM || pEhdr->e_entry == 0){
		nidcompat_free(elf_data);
		return 0;
	}

	if(pEhdr->e_entry > elf_size){
		printf("module is broken -> fw 0x%X, file %s (0x%lX-bytes), entry offset 0x%X\n", fw_version, ent->name, elf_size, pEhdr->e_entry);
		nidcompat_free(elf_data);
		return 0;
	}

	for(int i=0;i<pEhdr->e_phnum;i++){
		void *segment = (void *)(elf_data + pPhdr[i].p_offset);

		if(pPhdr[i].p_type == 1 && (pPhdr[i].p_flags & 7) == 5){
			const SceModuleEntryPoint *ep = (const SceModuleEntryPoint *)(segment + pEhdr->e_entry);
			nidcompat_create_db_range_by_elf(fw_version, pPhdr[i].p_vaddr, segment, ep);
		}
	}

	nidcompat_free(elf_data);

	return 0;
}



int nidcompat_create(void){

	int res;
	FSListEntry *pEnt = NULL;

	char path[0x400];

	for(int i=0;i<FWEntry_list_number;i++){
		snprintf(path, sizeof(path), "../vitafw/%s", FWEntry_list[i].name);

		res = fs_list_init(path, &pEnt, NULL, NULL);
		if(res >= 0){
			fs_list_execute(pEnt->child, nidcompat_create_callback, &(FWEntry_list[i]));
		}
		fs_list_fini(pEnt);
		pEnt = NULL;
	}

	printf("nidcompat_memory_usage_rate: 0x%lX\n", nidcompat_get_memory_usage_rate());

	nidcompat_save_current_db("./db/t");

	nidcompat_free_db();

	return 0;
}



int main(int argc, char **argp){

	// nidcompat_create();
	nidcompat_update_all();



	nidcompat_free_db();

	if(nidcompat_get_memory_usage_rate() != 0){
		printf("Warning: has memory leak/not free'd memory.\n");
		printf("nidcompat_memory_usage_rate: 0x%lX\n", nidcompat_get_memory_usage_rate());
	}

	return 0;
}
