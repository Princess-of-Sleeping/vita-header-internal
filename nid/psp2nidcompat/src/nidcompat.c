
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nidcompat.h"


NIDCompatDB *g_NIDCompatDB = NULL;


int nidcompat_is_available(void){
	return g_NIDCompatDB != NULL;
}

int nidcompat_insert_new_db(void){

	NIDCompatDB *db;

	db = nidcompat_malloc(sizeof(*db));
	if(db == NULL){
		return -1;
	}

	memset(db, 0, sizeof(*db));

	db->next = g_NIDCompatDB;

	g_NIDCompatDB = db;

	return 0;
}

int nidcompat_set_db_file_name(const char *name){

	if(g_NIDCompatDB == NULL){
		return -1;
	}

	name_copyin(name, &(g_NIDCompatDB->file_name));

	return 0;
}

int nidcompat_link_range(NIDCompatDBRangeCB *range_cb, NIDCompatDBRange *range){

	if(range_cb->head == NULL){
		range_cb->head = range;
	}

	if(range_cb->tail != NULL){
		range_cb->tail->next = range;
	}

	range_cb->tail = range;

	return 0;
}

int nidcompat_link_library(NIDCompatDBLibraryCB *library_cb, NIDCompatDBLibrary *library){

	if(library_cb->head == NULL){
		library_cb->head = library;
	}

	if(library_cb->tail != NULL){
		library_cb->tail->next = library;
	}

	library_cb->tail = library;

	return 0;
}

int nidcompat_link_entry(NIDCompatDBEntryCB *ent_cb, NIDCompatDBEntry *ent){

	if(ent_cb->head == NULL){
		ent_cb->head = ent;
	}

	if(ent_cb->tail != NULL){
		ent_cb->tail->next = ent;
	}

	ent_cb->tail = ent;

	return 0;
}

int nidcompat_add_host_module(uint32_t from, uint32_t to, const char *name){

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	if(range == NULL){
		return -1;
	}

	memset(range, 0, sizeof(*range));

	range->from = from;
	range->to = to;
	name_copyin(name, (char **)&(range->argp));

	nidcompat_link_range(&(g_NIDCompatDB->range), range);

	return 0;
}

int nidcompat_add_library(const char *name){

	NIDCompatDBLibrary *library;

	library = nidcompat_malloc(sizeof(*library));
	if(library == NULL){
		return -1;
	}

	memset(library, 0, sizeof(*library));
	name_copyin(name, &(library->name));

	nidcompat_link_library(&(g_NIDCompatDB->library), library);

	return 0;
}

int nidcompat_set_library_mode(const char *mode){

	if(strcmp(mode, "kernel") == 0){
		g_NIDCompatDB->library.tail->is_kernel = 1;
	}else{
		g_NIDCompatDB->library.tail->is_kernel = 0;
	}

	return 0;
}

int nidcompat_set_library_info(int version, uint32_t libnid, uint32_t from, uint32_t to){

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	if(range == NULL){
		return -1;
	}

	memset(range, 0, sizeof(*range));

	range->from = from;
	range->to   = to;
	range->argp = nidcompat_malloc(8);

	((uint32_t *)(range->argp))[0] = libnid;
	((uint32_t *)(range->argp))[1] = version;

	nidcompat_link_range(&(g_NIDCompatDB->library.tail->range), range);

	return 0;
}

int nidcompat_add_function(const char *name){

	NIDCompatDBEntry *ent;

	ent = nidcompat_malloc(sizeof(*ent));
	if(ent == NULL){
		return -1;
	}

	memset(ent, 0, sizeof(*ent));

	name_copyin(name, &(ent->name));

	nidcompat_link_entry(&(g_NIDCompatDB->library.tail->function), ent);

	g_NIDCompatDB->library.tail->last = ent;

	return 0;
}

int nidcompat_set_function_nid(uint32_t nid, uint32_t from, uint32_t to){

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	if(range == NULL){
		return -1;
	}

	memset(range, 0, sizeof(*range));

	range->from = from;
	range->to = to;
	range->argp = nidcompat_malloc(4);

	((uint32_t *)(range->argp))[0] = nid;

	nidcompat_link_range(&(g_NIDCompatDB->library.tail->function.tail->range), range);

	return 0;
}

int nidcompat_add_variable(const char *name){

	NIDCompatDBEntry *ent;

	ent = nidcompat_malloc(sizeof(*ent));
	if(ent == NULL){
		return -1;
	}

	memset(ent, 0, sizeof(*ent));

	name_copyin(name, &(ent->name));

	nidcompat_link_entry(&(g_NIDCompatDB->library.tail->variable), ent);

	g_NIDCompatDB->library.tail->last = ent;

	return 0;
}

int nidcompat_set_variable_nid(uint32_t nid, uint32_t from, uint32_t to){

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	if(range == NULL){
		return -1;
	}

	memset(range, 0, sizeof(*range));

	range->from = from;
	range->to = to;
	range->argp = nidcompat_malloc(4);

	((uint32_t *)(range->argp))[0] = nid;

	nidcompat_link_range(&(g_NIDCompatDB->library.tail->variable.tail->range), range);

	return 0;
}

int nidcompat_set_define(const char *define, uint32_t from, uint32_t to){

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	if(range == NULL){
		return -1;
	}

	memset(range, 0, sizeof(*range));

	range->from = from;
	range->to = to;
	name_copyin(define, (char **)&(range->argp));

	nidcompat_link_range(&(g_NIDCompatDB->library.tail->last->define_range), range);

	return 0;
}

int nidcompat_set_define_comment(const char *comment, uint32_t from, uint32_t to){

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	if(range == NULL){
		return -1;
	}

	memset(range, 0, sizeof(*range));

	range->from = from;
	range->to = to;
	name_copyin(comment, (char **)&(range->argp));

	nidcompat_link_range(&(g_NIDCompatDB->library.tail->last->define_comment_range), range);

	return 0;
}

int nidcompat_set_comment_wiki(const char *comment){

	if(g_NIDCompatDB->library.tail->last->comment_wiki != NULL){
		nidcompat_free(g_NIDCompatDB->library.tail->last->comment_wiki);
		g_NIDCompatDB->library.tail->last->comment_wiki = NULL;
	}

	name_copyin(comment, (char **)&(g_NIDCompatDB->library.tail->last->comment_wiki));

	return 0;
}


int nidcompat_free_range(NIDCompatDBRange *range){

	NIDCompatDBRange *next;

	while(range != NULL){
		next = range->next;

		nidcompat_free(range->argp);
		nidcompat_free(range);

		range = next;
	}

	return 0;
}

int nidcompat_free_ent(NIDCompatDBEntry *ent){

	NIDCompatDBEntry *ent_next;

	while(ent != NULL){
		ent_next = ent->next;

		nidcompat_free_range(ent->define_range.head);
		nidcompat_free_range(ent->define_comment_range.head);
		nidcompat_free_range(ent->range.head);
		nidcompat_free(ent->comment_wiki);
		nidcompat_free(ent->name);
		nidcompat_free(ent);

		ent = ent_next;
	}

	return 0;
}

int nidcompat_free_db(void){

	NIDCompatDB *db = g_NIDCompatDB, *db_next;

	while(db != NULL){
		db_next = db->next;

		NIDCompatDBLibrary *library = db->library.head, *next;

		while(library != NULL){
			next = library->next;

			nidcompat_free_range(library->range.head);
			nidcompat_free_ent(library->function.head);
			nidcompat_free_ent(library->variable.head);
			nidcompat_free(library->name);
			nidcompat_free(library);

			library = next;
		}

		nidcompat_free_range(db->range.head);
		nidcompat_free(db->file_name);
		nidcompat_free(db);

		db = db_next;
	}

	g_NIDCompatDB = NULL;

	return 0;
}

NIDCompatDBRange *nidcompat_get_ent_range_by_nid(const NIDCompatDBEntry *ent, uint32_t nid){

	NIDCompatDBRange *range;

	while(ent != NULL){
		range = ent->range.head;
		while(range != NULL){
			if(nid == ((uint32_t *)(range->argp))[0]){
				return range;
			}
			range = range->next;
		}

		ent = ent->next;
	}

	return NULL;
}

int nidcompat_create_library(uint32_t target_fw, const char *module_name, const char *name, int version, uint32_t libnid){

	NIDCompatDB *db = g_NIDCompatDB;

	while(db != NULL){
		NIDCompatDBLibrary *library = db->library.head;
		while(library != NULL){
			if(strcmp(library->name, name) == 0){
				NIDCompatDBRange *range = library->range.head;
				while(range != NULL){
					if(((uint32_t *)(range->argp))[0] == libnid && ((uint32_t *)(range->argp))[1] == version){

						if(target_fw < range->from){
							range->from = target_fw;
						}

						if(target_fw > range->to){
							range->to = target_fw;
						}
						break;
					}

					range = range->next;
				}

				if(range == NULL){
					range = nidcompat_malloc(sizeof(*range));
					memset(range, 0, sizeof(*range));
					range->from = target_fw;
					range->to   = target_fw;
					range->argp = nidcompat_malloc(8);
					((uint32_t *)(range->argp))[0] = libnid;
					((uint32_t *)(range->argp))[1] = version;
					nidcompat_link_range(&(library->range), range);
				}

				range = db->range.head;
				while(range != NULL){
					if(strcmp(module_name, (char *)range->argp) == 0){
						if(target_fw < range->from){
							range->from = target_fw;
						}

						if(target_fw > range->to){
							range->to = target_fw;
						}
						break;
					}

					range = range->next;
				}

				if(range == NULL){
					range = nidcompat_malloc(sizeof(*range));
					memset(range, 0, sizeof(*range));
					range->from = target_fw;
					range->to   = target_fw;
					name_copyin(module_name, (char **)&(range->argp));

					nidcompat_link_range(&(db->range), range);
				}

				return 0;
			}

			library = library->next;
		}

		db = db->next;
	}

	char file_name[0x80];
	snprintf(file_name, sizeof(file_name), "%s.txt", name);

	db = nidcompat_malloc(sizeof(*db));
	memset(db, 0, sizeof(*db));
	db->next = g_NIDCompatDB;
	name_copyin(file_name, &(db->file_name));

	NIDCompatDBRange *range;

	range = nidcompat_malloc(sizeof(*range));
	memset(range, 0, sizeof(*range));
	range->from = target_fw;
	range->to   = target_fw;
	name_copyin(module_name, (char **)&(range->argp));

	nidcompat_link_range(&(db->range), range);

	NIDCompatDBLibrary *library;

	library = nidcompat_malloc(sizeof(*library));
	memset(library, 0, sizeof(*library));
	name_copyin(name, &(library->name));

	range = nidcompat_malloc(sizeof(*range));
	memset(range, 0, sizeof(*range));
	range->from = target_fw;
	range->to   = target_fw;
	range->argp = nidcompat_malloc(8);
	((uint32_t *)(range->argp))[0] = libnid;
	((uint32_t *)(range->argp))[1] = version;
	nidcompat_link_range(&(library->range), range);
	nidcompat_link_library(&(db->library), library);

	if(strstr(name, "ForDriver") != NULL || strstr(name, "ForKernel") != NULL || strstr(name, "ForTool") != NULL || strstr(name, "ForDebugger") != NULL){
		library->is_kernel = 1;
	}

	g_NIDCompatDB = db;

	return 0;
}

int nidcompat_update_library_info(uint32_t target_fw, const char *module_name, const char *name, int version, uint32_t libnid, const uint32_t *nidtable, int function_num, int variable_num){

	NIDCompatDB *db = g_NIDCompatDB;

	while(db != NULL){

		NIDCompatDBLibrary *library = db->library.head;
		while(library != NULL){
			if(strcmp(library->name, name) == 0){
				NIDCompatDBRange *range = library->range.head;
				while(range != NULL){
					if(((uint32_t *)(range->argp))[0] == libnid && ((uint32_t *)(range->argp))[1] == version){

						if(target_fw < range->from){
							range->from = target_fw;
						}

						if(target_fw > range->to){
							range->to = target_fw;
						}
						break;
					}

					range = range->next;
				}

				if(range == NULL){
					range = nidcompat_malloc(sizeof(*range));
					memset(range, 0, sizeof(*range));

					range->from = target_fw;
					range->to   = target_fw;
					range->argp = nidcompat_malloc(8);
					((uint32_t *)(range->argp))[0] = libnid;
					((uint32_t *)(range->argp))[1] = version;
					nidcompat_link_range(&(library->range), range);
				}

				for(int i=0;i<function_num;i++){
					uint32_t nid = nidtable[i];

					range = nidcompat_get_ent_range_by_nid(library->function.head, nid);
					if(range != NULL){
						if(target_fw < range->from){
							range->from = target_fw;
						}

						if(target_fw > range->to){
							range->to = target_fw;
						}
					}else{
						char ent_name[0x110];

						snprintf(ent_name, sizeof(ent_name), "%s_%08X", name, nid);

						NIDCompatDBEntry *ent;

						ent = nidcompat_malloc(sizeof(*ent));
						memset(ent, 0, sizeof(*ent));
						name_copyin(ent_name, &(ent->name));

						range = nidcompat_malloc(sizeof(*range));
						memset(range, 0, sizeof(*range));

						range->from = target_fw;
						range->to   = target_fw;
						range->argp = nidcompat_malloc(4);
						((uint32_t *)(range->argp))[0] = nid;

						nidcompat_link_range(&(ent->range), range);
						nidcompat_link_entry(&(library->function), ent);
					}
				}

				for(int i=0;i<variable_num;i++){
					uint32_t nid = nidtable[function_num + i];

					range = nidcompat_get_ent_range_by_nid(library->variable.head, nid);
					if(range != NULL){
						if(target_fw < range->from){
							range->from = target_fw;
						}

						if(target_fw > range->to){
							range->to = target_fw;
						}
					}else{
						char ent_name[0x110];

						snprintf(ent_name, sizeof(ent_name), "%s_%08X", name, nid);

						NIDCompatDBEntry *ent;

						ent = nidcompat_malloc(sizeof(*ent));
						memset(ent, 0, sizeof(*ent));
						name_copyin(ent_name, &(ent->name));

						range = nidcompat_malloc(sizeof(*range));
						memset(range, 0, sizeof(*range));

						range->from = target_fw;
						range->to   = target_fw;
						range->argp = nidcompat_malloc(4);
						((uint32_t *)(range->argp))[0] = nid;

						nidcompat_link_range(&(ent->range), range);
						nidcompat_link_entry(&(library->variable), ent);
					}
				}


				range = db->range.head;
				while(range != NULL){
					if(strcmp(module_name, (char *)range->argp) == 0){
						if(target_fw < range->from){
							range->from = target_fw;
						}

						if(target_fw > range->to){
							range->to = target_fw;
						}
						break;
					}
					range = range->next;
				}

				if(range == NULL){
					range = nidcompat_malloc(sizeof(*range));
					memset(range, 0, sizeof(*range));
					range->from = target_fw;
					range->to   = target_fw;
					name_copyin(module_name, (char **)&(range->argp));
					nidcompat_link_range(&(db->range), range);
				}
			}

			library = library->next;
		}

		db = db->next;
	}

	return 0;
}



int nidcompat_save_current_db2file(NIDCompatDB *db, const char *path){

	FILE *fd = fopen(path, "wb");

	NIDCompatDBRange *range = db->range.head;

	while(range != NULL){

		if(range->from == range->to){
			fprintf(
				fd,
				"MODULE: %X.%03X.%03X %s\n",
				(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
				(char *)range->argp
			);
		}else{
			fprintf(
				fd,
				"MODULE: %X.%03X.%03X-%X.%03X.%03X %s\n",
				(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
				(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF,
				(char *)range->argp
			);
		}

		range = range->next;
	}

	fprintf(fd, "\n");

	NIDCompatDBLibrary *library = db->library.head;

	while(library != NULL){

		fprintf(fd, "LIBRARY: %s\n", library->name);
		fprintf(fd, "LIBRARY_MODE: %s\n", (library->is_kernel != 0) ? "kernel" : "user");

		range = library->range.head;

		while(range != NULL){
			if(range->from == range->to){
				fprintf(
					fd,
					"LIBRARY_INFO: %d 0x%08X %X.%03X.%03X\n",
					((uint32_t *)(range->argp))[1], ((uint32_t *)(range->argp))[0],
					(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF
				);
			}else{
				fprintf(
					fd,
					"LIBRARY_INFO: %d 0x%08X %X.%03X.%03X-%X.%03X.%03X\n",
					((uint32_t *)(range->argp))[1], ((uint32_t *)(range->argp))[0],
					(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
					(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF
				);
			}
			range = range->next;
		}

		fprintf(fd, "\n");

		NIDCompatDBEntry *ent;

		ent = library->function.head;

		while(ent != NULL){
			fprintf(fd, "FUNCTION: %s\n", ent->name);

			range = ent->range.head;

			while(range != NULL){
				if(range->from == range->to){
					fprintf(
						fd,
						"FUNCTION_NID: 0x%08X %X.%03X.%03X\n",
						((uint32_t *)(range->argp))[0],
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF
					);
				}else{
					fprintf(
						fd,
						"FUNCTION_NID: 0x%08X %X.%03X.%03X-%X.%03X.%03X\n",
						((uint32_t *)(range->argp))[0],
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF
					);
				}
				range = range->next;
			}

			range = ent->define_range.head;

			while(range != NULL){
				if(range->from == range->to){
					fprintf(
						fd,
						"DEFINE: %X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(char *)range->argp
					);
				}else{
					fprintf(
						fd,
						"DEFINE: %X.%03X.%03X-%X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF,
						(char *)range->argp
					);
				}
				range = range->next;
			}

			range = ent->define_comment_range.head;

			while(range != NULL){
				if(range->from == range->to){
					fprintf(
						fd,
						"DEFINE_COMMENT: %X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(char *)range->argp
					);
				}else{
					fprintf(
						fd,
						"DEFINE_COMMENT: %X.%03X.%03X-%X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF,
						(char *)range->argp
					);
				}
				range = range->next;
			}

			if(ent->comment_wiki != NULL){
				fprintf(fd, "COMMENT_WIKI: %s\n", ent->comment_wiki);
			}

			ent = ent->next;
		}

		fprintf(fd, "\n");

		ent = library->variable.head;

		while(ent != NULL){
			fprintf(fd, "VARIABLE: %s\n", ent->name);

			range = ent->range.head;

			while(range != NULL){
				if(range->from == range->to){
					fprintf(
						fd,
						"VARIABLE_NID: 0x%08X %X.%03X.%03X\n",
						((uint32_t *)(range->argp))[0],
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF
					);
				}else{
					fprintf(
						fd,
						"VARIABLE_NID: 0x%08X %X.%03X.%03X-%X.%03X.%03X\n",
						((uint32_t *)(range->argp))[0],
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF
					);
				}
				range = range->next;
			}

			range = ent->define_range.head;

			while(range != NULL){
				if(range->from == range->to){
					fprintf(
						fd,
						"DEFINE: %X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(char *)range->argp
					);
				}else{
					fprintf(
						fd,
						"DEFINE: %X.%03X.%03X-%X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF,
						(char *)range->argp
					);
				}
				range = range->next;
			}

			range = ent->define_comment_range.head;

			while(range != NULL){
				if(range->from == range->to){
					fprintf(
						fd,
						"DEFINE_COMMENT: %X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(char *)range->argp
					);
				}else{
					fprintf(
						fd,
						"DEFINE_COMMENT: %X.%03X.%03X-%X.%03X.%03X %s\n",
						(range->from >> 24) & 0xFF, (range->from >> 12) & 0xFFF, (range->from >> 0) & 0xFFF,
						(range->to >> 24) & 0xFF, (range->to >> 12) & 0xFFF, (range->to >> 0) & 0xFFF,
						(char *)range->argp
					);
				}
				range = range->next;
			}

			if(ent->comment_wiki != NULL){
				fprintf(fd, "COMMENT_WIKI: %s\n", ent->comment_wiki);
			}

			ent = ent->next;
		}

		fprintf(fd, "\n");

		library = library->next;
	}

	fclose(fd);
	fd = NULL;

	return 0;
}

int nidcompat_save_current_db(const char *output_dir){

	NIDCompatDB *db;
	char path[0x400];
	int count;

	count = 0;

	db = g_NIDCompatDB;
	while(db != NULL){
		if(db->file_name != NULL){
			snprintf(path, sizeof(path), "%s/%s", output_dir, db->file_name);
		}else{
			snprintf(path, sizeof(path), "%s/%d.txt", output_dir, count++);
		}

		nidcompat_save_current_db2file(db, path);

		db = db->next;
	}

	return 0;
}



