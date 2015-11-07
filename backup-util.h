/* 
 * File:   backup-util.h
 * Author: Alex de Kruijff <alex.de.kruijff@MazarineBlue.org>
 *
 * Created on November 6, 2015, 9:36 PM
 */

#ifndef BACKUP_UTIL_H
#define	BACKUP_UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <time.h>

int setBackupStamp(char *dst, size_t size, const char *base, const char *hostname, const struct tm *tm);
struct tm *getCurrentTime(bool local);
int getConfigFile(char *dst, size_t size, const char *prefix, const char *postfix);

#ifdef	__cplusplus
}
#endif

#endif	/* BACKUP_UTIL_H */

