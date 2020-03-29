#pragma once
#ifndef XSHELL_H
#define XSHELL_H

#include "..\stdafx.h"
#include <xbdm.h>
#include <stdio.h>
#include "OffsetManager.h"
#include <string>


static char* startXex;
static char* startPath;

int patch_Xshell_start_path(std::string newpath);
#endif