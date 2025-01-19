/*
 * FUSE wrapper for the littlefs
 *
 * Copyright (c) 2024, Axel Courtes
 * Copyright (c) 2022, the littlefs authors.
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LFS_FUSE_H
#define LFS_FUSE_H 1

#define FUSE_USE_VERSION 26

#ifdef linux
// needed for a few things fuse depends on
#define _XOPEN_SOURCE 700
#endif

#include <fuse/fuse.h>
#include "lfs.h"

/*******************************************************/
/* DEFINITIONS                                         */
/*******************************************************/

// littefs-fuse version
//
// Note this is different from the littlefs core version, and littlefs
// on-disk version
//
// Major (top-nibble), incremented on backwards incompatible changes
// Minor (bottom-nibble), incremented on feature additions
#define LFS_FUSE_VERSION 0x00020007
#define LFS_FUSE_VERSION_MAJOR (0xffff & (LFS_FUSE_VERSION >> 16))
#define LFS_FUSE_VERSION_MINOR (0xffff & (LFS_FUSE_VERSION >>  0))

/*******************************************************/
/* API                                                 */
/*******************************************************/

void lfs_fuse_defaults(struct lfs_config *config);
void *lfs_fuse_init(struct fuse_conn_info *conn);
int lfs_fuse_stat(void);
int lfs_fuse_format(void);
int lfs_fuse_migrate(void);
int lfs_fuse_mount(void);
void lfs_fuse_destroy(void *eh);
int lfs_fuse_statfs(const char *path, struct statvfs *s);
static void lfs_fuse_tostat(struct stat *s, struct lfs_info *info);
int lfs_fuse_getattr(const char *path, struct stat *s);
int lfs_fuse_access(const char *path, int mask);
int lfs_fuse_mkdir(const char *path, mode_t mode);
int lfs_fuse_opendir(const char *path, struct fuse_file_info *fi);
int lfs_fuse_releasedir(const char *path, struct fuse_file_info *fi);
int lfs_fuse_readdir(const char *path, void *buf,
    fuse_fill_dir_t filler, off_t offset,
    struct fuse_file_info *fi);
int lfs_fuse_rename(const char *from, const char *to);
int lfs_fuse_unlink(const char *path);
int lfs_fuse_open(const char *path, struct fuse_file_info *fi);
int lfs_fuse_release(const char *path, struct fuse_file_info *fi);
int lfs_fuse_fgetattr(const char *path, struct stat *s,
    struct fuse_file_info *fi);
int lfs_fuse_read(const char *path, char *buf, size_t size,
    off_t off, struct fuse_file_info *fi);
int lfs_fuse_write(const char *path, const char *buf, size_t size,
    off_t off, struct fuse_file_info *fi);
int lfs_fuse_fsync(const char *path, int isdatasync,
    struct fuse_file_info *fi);
int lfs_fuse_flush(const char *path, struct fuse_file_info *fi);
int lfs_fuse_create(const char *path, mode_t mode, struct fuse_file_info *fi);
int lfs_fuse_ftruncate(const char *path, off_t size,
    struct fuse_file_info *fi);
int lfs_fuse_truncate(const char *path, off_t size);
int lfs_fuse_link(const char *from, const char *to);
int lfs_fuse_mknod(const char *path, mode_t mode, dev_t dev);
int lfs_fuse_chmod(const char *path, mode_t mode);
int lfs_fuse_chown(const char *path, uid_t uid, gid_t gid);
int lfs_fuse_utimens(const char *path, const struct timespec ts[2]);

#endif /* LFS_FUSE_H */