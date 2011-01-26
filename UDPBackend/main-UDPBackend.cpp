/*****************************************************************************
*																			 *
*  OpenNI 1.0 Alpha															 *
*  Copyright (C) 2010 PrimeSense Ltd.										 *
*																			 *
*  This file is part of OpenNI.												 *
*																			 *
*  OpenNI is free software: you can redistribute it and/or modify			 *
*  it under the terms of the GNU Lesser General Public License as published	 *
*  by the Free Software Foundation, either version 3 of the License, or		 *
*  (at your option) any later version.										 *
*																			 *
*  OpenNI is distributed in the hope that it will be useful,				 *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of			 *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the				 *
*  GNU Lesser General Public License for more details.						 *
*																			 *
*  You should have received a copy of the GNU Lesser General Public License	 *
*  along with OpenNI. If not, see <http://www.gnu.org/licenses/>.			 *
*																			 *
*****************************************************************************/

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>
#include "SceneDrawer.h"
#include "SendUDP.h"
#include "Shared.h"

//---------------------------------------------------------------------------
// Globals
//---------------------------------------------------------------------------
xn::Context g_Context;
xn::DepthGenerator g_DepthGenerator;
xn::UserGenerator g_UserGenerator;

XnBool g_bNeedPose = FALSE;
XnChar g_strPose[20] = "";
XnBool g_bDrawBackground = TRUE;
XnBool g_bDrawPixels = TRUE;
XnBool g_bDrawSkeleton = TRUE;
XnBool g_bPrintID = TRUE;
XnBool g_bPrintState = TRUE;

#if (XN_PLATFORM == XN_PLATFORM_MACOSX)
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#define GL_WIN_SIZE_X 360
#define GL_WIN_SIZE_Y 240

XnBool g_bPause = false;
XnBool g_bRecord = false;

XnBool g_bQuit = false;

//---------------------------------------------------------------------------
// Code
//---------------------------------------------------------------------------

void CleanupExit()
{
	g_Context.Shutdown();

	exit (1);
}

// Callback: New user was detected
void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	printf("New User %d\n", nId);
	// New user found
	if (g_bNeedPose)
	{
		g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
	}
	else
	{
		g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
	}
}
// Callback: An existing user was lost
void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
{
	printf("Lost user %d\n", nId);
}
// Callback: Detected a pose
void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie)
{
	printf("Pose %s detected for user %d\n", strPose, nId);
	g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
	g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
}
// Callback: Started calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie)
{
	printf("Calibration started for user %d\n", nId);
}
// Callback: Finished calibration
void XN_CALLBACK_TYPE UserCalibration_CalibrationEnd(xn::SkeletonCapability& capability, XnUserID nId, XnBool bSuccess, void* pCookie)
{
	if (bSuccess)
	{
		// Calibration succeeded
		printf("Calibration complete, start tracking user %d\n", nId);
		g_UserGenerator.GetSkeletonCap().StartTracking(nId);
	}
	else
	{
		// Calibration failed
		printf("Calibration failed for user %d\n", nId);
		if (g_bNeedPose)
		{
			g_UserGenerator.GetPoseDetectionCap().StartPoseDetection(g_strPose, nId);
		}
		else
		{
			g_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
		}
	}
}

void SendUDPSkeletalData(XnUserID player) {

	if (!g_UserGenerator.GetSkeletonCap().IsTracking(player))
	{
		printf("not tracked!\n");
		return;
	}

	XnSkeletonJointPosition leftHand, rightHand, leftElbow, rightElbow, leftShoulder, rightShoulder, torso, leftHip, rightHip, leftKnee, rightKnee, leftAnkle, rightAnkle, leftFoot, rightFoot, head;
	g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_HAND, leftHand);
	g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_HAND, rightHand);
  
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_ELBOW, leftElbow);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_ELBOW, rightElbow);
  
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_SHOULDER, leftShoulder);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_SHOULDER, rightShoulder);
  
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_TORSO, torso);
  
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_HIP, leftHip);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_HIP, rightHip);

  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_KNEE, leftKnee);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_KNEE, rightKnee);

  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_ANKLE, leftAnkle);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_ANKLE, rightAnkle);
  
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_LEFT_FOOT, leftFoot);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_RIGHT_FOOT, rightFoot);
  g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(player, XN_SKEL_HEAD, head);

  // We could check for confidence if we wanted
	//if (leftHand.fConfidence < 0.5 || rightHand.fConfidence < 0.5)
	//{
	//	return;
	//}

	char packet[1000];
  // Holy crap this is a hack, TODO: do something not completely stupid
/*	sprintf(packet, "lhx%0.3fy%0.3fz%0.3f rhx%0.3fy%0.3fz%0.3f lex%0.3fy%0.3fz%0.3f rex%0.3fy%0.3fz%0.3f lcx%0.3fy%0.3fz%0.3f rcx%0.3fy%0.3fz%0.3f ttx%0.3fy%0.3fz%0.3f lix%0.3fy%0.3fz%0.3f rix%0.3fy%0.3fz%0.3f lkx%0.3fy%0.3fz%0.3f rkx%0.3fy%0.3fz%0.3f lax%0.3fy%0.3fz%0.3f rax%0.3fy%0.3fz%0.3f lfx%0.3fy%0.3fz%0.3f rfx%0.3fy%0.3fz%0.3f hhx%0.3fy%0.3fz%0.3f ",
          leftHand.position.X, leftHand.position.Y, leftHand.position.Z,
          rightHand.position.X, rightHand.position.Y, rightHand.position.Z,

          leftElbow.position.X, leftElbow.position.Y, leftElbow.position.Z,
          rightElbow.position.X, rightElbow.position.Y, rightElbow.position.Z,

          leftCollar.position.X, leftCollar.position.Y, leftCollar.position.Z,
          rightCollar.position.X, rightCollar.position.Y, rightCollar.position.Z,

          torso.position.X, torso.position.Y, torso.position.Z,

          leftHip.position.X, leftHip.position.Y, leftHip.position.Z,
          rightHip.position.X, rightHip.position.Y, rightHip.position.Z,

          leftKnee.position.X, leftKnee.position.Y, leftKnee.position.Z,
          rightKnee.position.X, rightKnee.position.Y, rightKnee.position.Z,

          //leftAnkle.position.X, leftAnkle.position.Y, leftAnkle.position.Z,
          //rightAnkle.position.X, rightAnkle.position.Y, rightAnkle.position.Z,

          leftFoot.position.X, leftFoot.position.Y, leftFoot.position.Z, 
          rightFoot.position.X, rightFoot.position.Y, rightFoot.position.Z, 
          head.position.X, head.position.Y, head.position.Z);
*/
	sprintf(packet, "lhx%0.3fy%0.3fz%0.3f rhx%0.3fy%0.3fz%0.3f lex%0.3fy%0.3fz%0.3f rex%0.3fy%0.3fz%0.3f lsx%0.3fy%0.3fz%0.3f rsx%0.3fy%0.3fz%0.3f ttx%0.3fy%0.3fz%0.3f lix%0.3fy%0.3fz%0.3f rix%0.3fy%0.3fz%0.3f lkx%0.3fy%0.3fz%0.3f rkx%0.3fy%0.3fz%0.3f lfx%0.3fy%0.3fz%0.3f rfx%0.3fy%0.3fz%0.3f hhx%0.3fy%0.3fz%0.3f ",
          leftHand.position.X, leftHand.position.Y, leftHand.position.Z,
          rightHand.position.X, rightHand.position.Y, rightHand.position.Z,

          leftElbow.position.X, leftElbow.position.Y, leftElbow.position.Z,
          rightElbow.position.X, rightElbow.position.Y, rightElbow.position.Z,

          leftShoulder.position.X, leftShoulder.position.Y, leftShoulder.position.Z,
          rightShoulder.position.X, rightShoulder.position.Y, rightShoulder.position.Z,

          torso.position.X, torso.position.Y, torso.position.Z,

          leftHip.position.X, leftHip.position.Y, leftHip.position.Z,
          rightHip.position.X, rightHip.position.Y, rightHip.position.Z,

          leftKnee.position.X, leftKnee.position.Y, leftKnee.position.Z,
          rightKnee.position.X, rightKnee.position.Y, rightKnee.position.Z,

          //leftAnkle.position.X, leftAnkle.position.Y, leftAnkle.position.Z,
          //rightAnkle.position.X, rightAnkle.position.Y, rightAnkle.position.Z,

          leftFoot.position.X, leftFoot.position.Y, leftFoot.position.Z, 
          rightFoot.position.X, rightFoot.position.Y, rightFoot.position.Z, 
          head.position.X, head.position.Y, head.position.Z);

/*
	sprintf(packet, "lhx%0.3fy%0.3fz%0.3f rhx%0.3fy%0.3fz%0.3f lfx%0.3fy%0.3fz%0.3f rfx%0.3fy%0.3fz%0.3f hhx%0.3fy%0.3fz%0.3f",
          leftHand.position.X, leftHand.position.Y, leftHand.position.Z,
          rightHand.position.X, rightHand.position.Y, rightHand.position.Z,
          leftFoot.position.X, leftFoot.position.Y, leftFoot.position.Z, 
          rightFoot.position.X, rightFoot.position.Y, rightFoot.position.Z, 
          head.position.X, head.position.Y, head.position.Z);
*/
	//printf("sending data: %s\n", packet);
	SUDP_SendMsg(packet, strlen(packet));
}

// this function is called each frame
void glutDisplay (void)
{

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Setup the OpenGL viewpoint
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	xn::SceneMetaData sceneMD;
	xn::DepthMetaData depthMD;
	g_DepthGenerator.GetMetaData(depthMD);
	glOrtho(0, depthMD.XRes(), depthMD.YRes(), 0, -1.0, 1.0);

	glDisable(GL_TEXTURE_2D);

	if (!g_bPause)
	{
		// Read next available data
		g_Context.WaitAndUpdateAll();
	}

		// Process the data
		g_DepthGenerator.GetMetaData(depthMD);
		g_UserGenerator.GetUserPixels(0, sceneMD);
		DrawDepthMap(depthMD, sceneMD);

	glutSwapBuffers();

  XnUserID trackingUser = FirstTrackingUser(g_UserGenerator);
	SendUDPSkeletalData(trackingUser);
}

void glutIdle (void)
{
	if (g_bQuit) {
		CleanupExit();
	}

	// Display the frame
	glutPostRedisplay();
}

void glutKeyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		CleanupExit();
	case 'b':
		// Draw background?
		g_bDrawBackground = !g_bDrawBackground;
		break;
	case 'x':
		// Draw pixels at all?
		g_bDrawPixels = !g_bDrawPixels;
		break;
	case 's':
		// Draw Skeleton?
		g_bDrawSkeleton = !g_bDrawSkeleton;
		break;
	case 'i':
		// Print label?
		g_bPrintID = !g_bPrintID;
		break;
	case 'l':
		// Print ID & state as label, or only ID?
		g_bPrintState = !g_bPrintState;
		break;
	case'p':
		g_bPause = !g_bPause;
		break;
	}
}
void glInit (int * pargc, char ** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
	glutCreateWindow ("Prime Sense User Tracker Viewer");
	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);

	glutKeyboardFunc(glutKeyboard);
	glutDisplayFunc(glutDisplay);
	glutIdleFunc(glutIdle);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

#define SAMPLE_XML_PATH "./SamplesConfig.xml"

#define CHECK_RC(nRetVal, what)										\
	if (nRetVal != XN_STATUS_OK)									\
	{																\
		printf("%s failed: %s\n", what, xnGetStatusString(nRetVal));\
		return nRetVal;												\
	}

int main(int argc, char **argv)
{
	XnStatus nRetVal = XN_STATUS_OK;

	if (argc > 1)
	{
		nRetVal = g_Context.Init();
		CHECK_RC(nRetVal, "Init");
		nRetVal = g_Context.OpenFileRecording(argv[1]);
		if (nRetVal != XN_STATUS_OK)
		{
			printf("Can't open recording %s: %s\n", argv[1], xnGetStatusString(nRetVal));
			return 1;
		}
	}
	else
	{
		xn::EnumerationErrors errors;
		nRetVal = g_Context.InitFromXmlFile(SAMPLE_XML_PATH, &errors);
		if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
		{
			XnChar strError[1024];
			errors.ToString(strError, 1024);
			printf("%s\n", strError);
			return (nRetVal);
		}
		else if (nRetVal != XN_STATUS_OK)
		{
			printf("Open failed: %s\n", xnGetStatusString(nRetVal));
			return (nRetVal);
		}
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	CHECK_RC(nRetVal, "Find depth generator");
	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		nRetVal = g_UserGenerator.Create(g_Context);
		CHECK_RC(nRetVal, "Find user generator");
	}

	XnCallbackHandle hUserCallbacks, hCalibrationCallbacks, hPoseCallbacks;
	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
	{
		printf("Supplied user generator doesn't support skeleton\n");
		return 1;
	}
	g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
	g_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(UserCalibration_CalibrationStart, UserCalibration_CalibrationEnd, NULL, hCalibrationCallbacks);

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
	{
		g_bNeedPose = TRUE;
		if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
		{
			printf("Pose required, but not supported\n");
			return 1;
		}
		g_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(UserPose_PoseDetected, NULL, NULL, hPoseCallbacks);
		g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");

	glInit(&argc, argv);
	SUDP_Init("127.0.0.1");
	glutMainLoop();

}
