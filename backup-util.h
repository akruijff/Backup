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

int getConfigFile(char *dst, size_t size, const char *prefix, const char *postfix);

#ifdef	__cplusplus
}
#endif

#endif	/* BACKUP_UTIL_H */

