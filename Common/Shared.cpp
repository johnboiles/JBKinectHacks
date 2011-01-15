/*
 *  Shared.c
 *  JBMouseControllerXcode
 *
 *  Created by John Boiles on 1/13/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Shared.h"

XnUserID FirstTrackingUser(xn::UserGenerator userGenerator) {
	XnUserID aUsers[10];
	XnUInt16 nUsers = 10;
	userGenerator.GetUsers(aUsers, nUsers);
	// The first user that's tracking will be in control
	for (int i = 0; i < nUsers; ++i) {
		if(userGenerator.GetSkeletonCap().IsTracking(aUsers[i])){
			return aUsers[i];
		}
	}
  return NULL;
}