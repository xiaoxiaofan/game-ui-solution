// TestDESDlg.cpp : implementation file
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#include "stdafx.h"

#include <streams.h>
#include <qedit.h>
//#include <dxutil.h>

#include "TestDES.h"
#include "TestDESDlg.h"

#include "CDESXml.h"
#include "CDESPropertySetter.h"
#include "CDESEffect.h"
#include "CDESTransition.h"
#include "StWaitCursor.h"
#include "CHelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDESDlg dialog

CTestDESDlg::CTestDESDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDESDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDESDlg)
	mTimelineStartTime = 0.0;
	mTimelineStopTime = 0.0;
	mSaveFilename = _T("C:\\DES.xtl");
	mMediaStartTime = 0.0;
	mMediaStopTime = 0.0;
	mTransTypeValue = 0;
	mMixAudioFilename = _T("");
	mVideoSrcFile = _T("");
	mEffectStartTime = 0.0;
	mEffectStopTime = 0.0;
	mPipFilename = _T("");
	mImageGray = FALSE;
	mImageInvert = FALSE;
	mImageMirror = FALSE;
	mImageXRay = FALSE;
	mImageRotation = FALSE;
	mImageOpacity = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDESDlg)
	DDX_Control(pDX, IDC_BUTTON_PIPFILE, mPipFileBrowser);
	DDX_Control(pDX, IDC_BUTTON_VIDEO_SRC, mVideoSourceBrowser);
	DDX_Control(pDX, IDC_BUTTON_AUDIO_MIX, mAudioMixFileBrowser);
	DDX_Control(pDX, IDC_TRANS_TYPE, mTransType);
	DDX_Control(pDX, IDC_TITLE_TYPE, mTransTitleType);
	DDX_Control(pDX, IDC_PROP_APPLY, mPropApply);
	DDX_Control(pDX, IDC_FRAME_TRANS, mFrameTrans);
	DDX_Control(pDX, IDC_TITLE_TRANS, mTitleTrans);
	DDX_Control(pDX, IDC_TRANS_APPLY, mTransApply);
	DDX_Control(pDX, IDC_VIDEO_WND, mVideoWindow);
	DDX_Control(pDX, IDC_TRANSITIONS, mComboTrans);
	DDX_Control(pDX, IDC_EFFECTS, mComboEffects);
	DDX_Text(pDX, IDC_START_TIME, mTimelineStartTime);
	DDX_Text(pDX, IDC_STOP_TIME, mTimelineStopTime);
	DDX_Text(pDX, IDC_FILENAME, mSaveFilename);
	DDX_Text(pDX, IDC_MEDIA_START_TIME, mMediaStartTime);
	DDX_Text(pDX, IDC_MEDIA_STOP_TIME, mMediaStopTime);
	DDX_Text(pDX, IDC_TRANS_TYPE, mTransTypeValue);
	DDX_Text(pDX, IDC_AUDIO_FILE, mMixAudioFilename);
	DDX_Text(pDX, IDC_VIDEO_SRCFILE, mVideoSrcFile);
	DDX_Text(pDX, IDC_EFFECT_START_TIME, mEffectStartTime);
	DDX_Text(pDX, IDC_EFFECT_STOP_TIME, mEffectStopTime);
	DDX_Text(pDX, IDC_PIP_FILENAME, mPipFilename);
	DDX_Check(pDX, IDC_IMGAE_GRAY, mImageGray);
	DDX_Check(pDX, IDC_IMGAE_INVERT, mImageInvert);
	DDX_Check(pDX, IDC_IMGAE_MIRROR, mImageMirror);
	DDX_Check(pDX, IDC_IMGAE_XRAY, mImageXRay);
	DDX_Check(pDX, IDC_IMGAE_ROTATION, mImageRotation);
	DDX_Check(pDX, IDC_IMGAE_OPACITY, mImageOpacity);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDESDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDESDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUT_SRC1, OnButSrc1)
	ON_BN_CLICKED(IDC_PROP_APPLY, OnPropApply)
	ON_BN_CLICKED(IDC_BUT_SRC2, OnButSrc2)
	ON_BN_CLICKED(IDC_BUT_TRANS1, OnButTrans1)
	ON_BN_CLICKED(IDC_BUT_PREVIEW, OnButPreview)
	ON_BN_CLICKED(IDC_BUT_PLAY, OnButPlay)
	ON_BN_CLICKED(IDC_BUT_PAUSE, OnButPause)
	ON_BN_CLICKED(IDC_BUT_STOP, OnButStop)
	ON_BN_CLICKED(IDC_AUDIO_BACK, OnAudioBack)
	ON_BN_CLICKED(IDC_BUT_SAVE, OnButSave)
	ON_BN_CLICKED(IDC_BUT_MUX, OnButMux)
	ON_BN_CLICKED(IDC_BUT_TRANS2, OnButTrans2)
	ON_BN_CLICKED(IDC_BUT_SRC3, OnButSrc3)
	ON_BN_CLICKED(IDC_BUT_TRANS3, OnButTrans3)
	ON_BN_CLICKED(IDC_BUT_SRC4, OnButSrc4)
	ON_BN_CLICKED(IDC_BUT_TRANS4, OnButTrans4)
	ON_BN_CLICKED(IDC_BUT_SRC5, OnButSrc5)
	ON_CBN_SELCHANGE(IDC_TRANSITIONS, OnSelchangeTransitions)
	ON_CBN_SELCHANGE(IDC_EFFECTS, OnSelchangeEffects)
	ON_BN_CLICKED(IDC_BUTTON_SAVEGRF, OnButtonSavegrf)
	ON_BN_CLICKED(IDC_TRANS_APPLY, OnTransApply)
	ON_BN_CLICKED(IDC_BUTTON_PIPFILE, OnButtonPipfile)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_MIX, OnButtonAudioMix)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDESDlg message handlers

BOOL CTestDESDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Init();
	bool pass = UDESUtils::QueryLocalAvailableEffects();//-----------------------
	pass = UDESUtils::QueryLocalAvailableTransitions();//------------------------

	FillEffectComboBox();
	FillTransitionComboBox();

	if (mTimeLine.Initialize())
	{
		pass = mFileDetector.Initialize();

		pass = mRenderEngine.Initialize();
		mRenderEngine.SetTimelineObject(mTimeLine);

		mVideoGroup = new CDESGroup(&mTimeLine);
		mAudioGroup = new CDESGroup(&mTimeLine);
		mVideoTrackMajor1 = new CDESTrack(&mTimeLine);
		mVideoTrackMajor2 = new CDESTrack(&mTimeLine);
		mVideoTrackMinor1 = new CDESTrack(&mTimeLine);
		mAudioTrackMajor1 = new CDESTrack(&mTimeLine);
		mAudioTrackMajor2 = new CDESTrack(&mTimeLine);
		mAudioTrackMinor1 = new CDESTrack(&mTimeLine);
		pass = mVideoGroup->Initialize();
		mTimeLine.AddGroup(mVideoGroup);
		mVideoGroup->SetGroupType(TRUE);
		pass = mAudioGroup->Initialize();
		mTimeLine.AddGroup(mAudioGroup);
		mAudioGroup->SetGroupType(FALSE);

		pass = mVideoTrackMajor1->Initialize();
		pass = mVideoTrackMajor2->Initialize();
		pass = mVideoTrackMinor1->Initialize();
		mVideoGroup->VTrackInsBefore(*mVideoTrackMajor1, -1);
		mVideoGroup->VTrackInsBefore(*mVideoTrackMajor2, -1);
		mVideoGroup->VTrackInsBefore(*mVideoTrackMinor1, -1);

		pass = mAudioTrackMajor1->Initialize();
		pass = mAudioTrackMajor2->Initialize();
		pass = mAudioTrackMinor1->Initialize();
		mAudioGroup->VTrackInsBefore(*mAudioTrackMajor1, -1);
		mAudioGroup->VTrackInsBefore(*mAudioTrackMajor2, -1);
		mAudioGroup->VTrackInsBefore(*mAudioTrackMinor1, -1);
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDESDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDESDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDESDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	Uninit();
}


//////////////////////////////////////////////////////////////////////
void CTestDESDlg::Init(void)
{
	mVideoGroup = NULL;
	mAudioGroup = NULL;
	mVideoTrackMajor1 = NULL;
	mVideoTrackMajor2 = NULL;
	mVideoTrackMinor1 = NULL;

	mAudioTrackMajor1 = NULL;
	mAudioTrackMajor2 = NULL;
	mAudioTrackMinor1 = NULL;

	mCurrentVideoTrack  = NULL;
	mCurrentVideoSource = NULL;
	mCurrentAudioSource = NULL;
	mCurrentVideoEffect = NULL;
	mPipTransition      = NULL;
	for (int i = 0; i < MAX_SRC; i++)
	{
		mVideoSources[i] = NULL;
		mAudioSources[i] = NULL;
		mVideoEffects[i] = NULL;
		mPipVideoSources[i] = NULL;
		mAudioMixings[i] = NULL;
	}
	mCurrentTransNode    = 0;
	mCurrentSourceNode   = 0;
	UpdateProgressMark(1);
}

void CTestDESDlg::Uninit(void)
{
	if (mVideoGroup)
	{
		delete mVideoGroup;
		mVideoGroup = NULL;
	}
	if (mAudioGroup)
	{
		delete mAudioGroup;
		mAudioGroup = NULL;
	}
	if (mVideoTrackMajor1)
	{
		delete mVideoTrackMajor1;
		mVideoTrackMajor1 = NULL;
	}
	if (mVideoTrackMajor2)
	{
		delete mVideoTrackMajor2;
		mVideoTrackMajor2 = NULL;
	}
	if (mVideoTrackMinor1)
	{
		delete mVideoTrackMinor1;
		mVideoTrackMinor1 = NULL;
	}
	if (mAudioTrackMajor1)
	{
		delete mAudioTrackMajor1;
		mAudioTrackMajor1 = NULL;
	}
	if (mAudioTrackMajor2)
	{
		delete mAudioTrackMajor2;
		mAudioTrackMajor2 = NULL;
	}
	if (mAudioTrackMinor1)
	{
		delete mAudioTrackMinor1;
		mAudioTrackMinor1 = NULL;
	}

	if (mPipTransition)
	{
		delete mPipTransition;
		mPipTransition = NULL;
	}

	// Remove source list
/*	POSITION pos = VideoSourceList.GetHeadPosition();
	while (pos)
	{
		CDESSource * pSource = (CDESSource *) VideoSourceList.GetNext(pos);
		delete pSource;
	}
	VideoSourceList.RemoveAll();

	pos = AudioSourceList.GetHeadPosition();
	while (pos)
	{
		CDESSource * pSource = (CDESSource *) AudioSourceList.GetNext(pos);
		delete pSource;
	}
	AudioSourceList.RemoveAll();*/
	for (int i = 0; i < MAX_SRC ; i++)
	{
		if (mVideoSources[i])
		{
			delete mVideoSources[i];
			mVideoSources[i] = NULL;
		}
		if (mAudioSources[i])
		{
			delete mAudioSources[i];
			mAudioSources[i] = NULL;
		}
		if (mVideoEffects[i])
		{
			delete mVideoEffects[i];
			mVideoEffects[i] = NULL;
		}
		if (mPipVideoSources[i])
		{
			delete mPipVideoSources[i];
			mPipVideoSources[i] = NULL;
		}
		if (mAudioMixings[i])
		{
			delete mAudioMixings[i];
			mAudioMixings[i] = NULL;
		}
	}
	
	POSITION pos = AudioBackgroundList.GetHeadPosition();
	while (pos)
	{
		CDESSource * pSource = (CDESSource *) AudioBackgroundList.GetNext(pos);
		delete pSource;
	}
	AudioBackgroundList.RemoveAll();
}
//////////////////////////////////////////////////////////////////////////////////


void CTestDESDlg::FillEffectComboBox(void)
{
	POSITION pos = UDESUtils::sEffectList.GetHeadPosition();
	while (pos)
	{
		CDESGuid  Guid = UDESUtils::sEffectList.GetNext(pos);
		mComboEffects.AddString(Guid.mFriendlyName);
	}
	mComboEffects.AddString("None");
}

void CTestDESDlg::FillTransitionComboBox(void)
{
	POSITION pos = UDESUtils::sTransitionList.GetHeadPosition();
	while (pos)
	{
		CDESGuid  Guid = UDESUtils::sTransitionList.GetNext(pos);
		mComboTrans.AddString(Guid.mFriendlyName);
	}
//	mComboTrans.AddString("None");
}

bool CTestDESDlg::OpenFileDialog(CString & inFilter, CString & outFileName)
{
	CFileDialog   dlgOpen(TRUE, NULL, NULL, OFN_HIDEREADONLY, inFilter, this);
	if (IDOK == dlgOpen.DoModal()) 
	{
		outFileName = dlgOpen.GetPathName();
		return true;
	}
	return false;
}

// Add source...
void CTestDESDlg::OnButSrc1() 
{
	// Has no valid source file
	if (mVideoSources[0] == NULL)
	{
		CString       fileName;
		if (EnterNewVideoSource(mVideoTrackMajor1, 1, fileName))
		{
			double timeStart = 0, timeStop = 0;
			mVideoTrackMajor2->GetStartStop2(&timeStart, &timeStop);
			// If static image file, set default bps to 0.0
			if (IsImageFile(fileName))
			{
				mCurrentVideoSource->SetStartStop2(timeStop, timeStop + IMAGE_DURATION);
				mCurrentVideoSource->SetMediaTimes2(0, IMAGE_DURATION);
				mCurrentVideoSource->SetDefaultFPS(0);
			}
			else
			{
				double  timeLength = 0;
				mFileDetector.put_Filename(fileName);
				mFileDetector.get_StreamLength(&timeLength);
				mCurrentVideoSource->SetMediaLength2(timeLength);
				mCurrentVideoSource->SetStartStop2(timeStop, timeStop + timeLength);
				mCurrentVideoSource->SetMediaTimes2(0, timeLength);

				// Keep audio syc with video using video track's timeStart and timeStop
				if (mCurrentAudioSource)
				{
					mCurrentAudioSource->SetMediaLength2(timeLength);
					mCurrentAudioSource->SetStartStop2(timeStop, timeStop + timeLength);
					mCurrentAudioSource->SetMediaTimes2(0, timeLength);
				}
			}
		}
	}

	// Switch to property setting pad of the current source
	if (mVideoSources[0])
	{
		UpdateProgressMark(1);

		EnableTransitionSetting(FALSE);
		EnableSourceSetting(TRUE);

		mCurrentSourceNode = 1;
		mCurrentVideoTrack  = mVideoTrackMajor1;
		mCurrentVideoEffect = mVideoEffects[0];
		mCurrentVideoSource = mVideoSources[0];
		mCurrentAudioSource = mAudioSources[0];
		ReflectNewSource(mCurrentVideoSource);

		////////////////////// Pause preview graph ////////////////////////
		PreviewCurrentSource();
		////////////////////////////////////////////////////////////////////
	}
}

bool CTestDESDlg::EnterNewVideoSource(CDESTrack * inTargetTrack, 
									  int inSourceIndex, CString & outFileName)
{
	CString       strFilter = "Avi File (*.avi)|*.avi|";
	strFilter += "Mpeg File (*.mpg;*.mpeg)|*.mpg;*.mpeg|";
	strFilter += "Image File (*.bmp;*.jpg;*.bmp;*.jpg;*.jpeg;*.gif;*.tga)|*.bmp;*.jpg;*.bmp;*.jpg;*.jpeg;*.gif;*.tga|";
	if (OpenFileDialog(strFilter, outFileName))
	{
		mCurrentVideoSource  = new CDESSource(&mTimeLine);
		bool pass = mCurrentVideoSource->Initialize();
		mCurrentVideoSource->SetMediaName(outFileName);
		mVideoSources[inSourceIndex - 1] = mCurrentVideoSource;
	//	VideoSourceList.AddTail(mCurrentVideoSource);
		pass = inTargetTrack->SrcAdd(*mCurrentVideoSource);
		
		long streamCount = 0;
		pass = mFileDetector.put_Filename(outFileName);
		pass = mFileDetector.get_OutputStreams(&streamCount);
		mCurrentAudioSource = NULL;
		// If not contain audio stream, not add this as audio source!!
		if (streamCount > 1)
		{
			mCurrentAudioSource = new CDESSource(&mTimeLine);
			pass = mCurrentAudioSource->Initialize();
			mCurrentAudioSource->SetMediaName(outFileName);
			mAudioSources[inSourceIndex - 1] = mCurrentAudioSource;
		//	AudioSourceList.AddTail(mCurrentAudioSource);
			pass = mAudioTrackMajor1->SrcAdd(*mCurrentAudioSource);
		}
		
		return true;
	}
	return false;
}

void CTestDESDlg::ReflectNewSource(CDESSource * inSource)
{
	double timeStart = 0, timeStop = 0;
	inSource->GetMediaTimes2(&timeStart, &timeStop);
	mMediaStartTime = timeStart;
	mMediaStopTime  = timeStop;
	inSource->GetStartStop2(&timeStart, &timeStop);
	mTimelineStartTime = timeStart;
	mTimelineStopTime  = timeStop;

	char   szFile[MAX_PATH];
	inSource->GetMediaName(szFile);
	mVideoSrcFile = szFile;

	mEffectStartTime = 0;
	mEffectStopTime  = 0;
	if (mCurrentVideoEffect)
	{
		mCurrentVideoEffect->GetStartStop2(&timeStart, &timeStop);
		mEffectStartTime = timeStart;
		mEffectStopTime  = timeStop;
	}

	UpdateData(FALSE);
}

void CTestDESDlg::OnButSrc2() 
{
	// Has no valid source file
	if (mVideoSources[0] == NULL)
		return;

	if (mVideoSources[1] == NULL)
	{
		CString       fileName;
		if (EnterNewVideoSource(mVideoTrackMajor2, 2, fileName))
		{
			double timeStart = 0, timeStop = 0;
			mVideoTrackMajor1->GetStartStop2(&timeStart, &timeStop);
			// If static image file, set default bps to 0.0
			if (IsImageFile(fileName))
			{
				mCurrentVideoSource->SetStartStop2(timeStop, timeStop + IMAGE_DURATION);
				mCurrentVideoSource->SetMediaTimes2(0, IMAGE_DURATION);
				mCurrentVideoSource->SetDefaultFPS(0);
			}
			else
			{
				double  timeLength = 0;
				mFileDetector.put_Filename(fileName);
				mFileDetector.get_StreamLength(&timeLength);

				mCurrentVideoSource->SetMediaLength2(timeLength);
				mCurrentVideoSource->SetStartStop2(timeStop, timeStop + timeLength);
				mCurrentVideoSource->SetMediaTimes2(0, timeLength);

				// Keep audio syc with video using video track's timeStart and timeStop
				if (mCurrentAudioSource)
				{
					mCurrentAudioSource->SetMediaLength2(timeLength);
					mCurrentAudioSource->SetStartStop2(timeStop, timeStop + timeLength);
					mCurrentAudioSource->SetMediaTimes2(0, timeLength);
				}
			}
		}
	}

	// Switch to property setting pad of the current source
	if (mVideoSources[1])
	{
		UpdateProgressMark(3);

		EnableTransitionSetting(FALSE);
		EnableSourceSetting(TRUE);

		mCurrentSourceNode = 2;
		mCurrentVideoTrack  = mVideoTrackMajor2;
		mCurrentVideoEffect = mVideoEffects[1];
		mCurrentVideoSource = mVideoSources[1];
		mCurrentAudioSource = mAudioSources[1];
		ReflectNewSource(mCurrentVideoSource);

		////////////////////// Pause preview graph ////////////////////////
		PreviewCurrentSource();
		////////////////////////////////////////////////////////////////////
	}
}


void CTestDESDlg::EnterNewTransition(void)
{
	int nIndex = mComboTrans.GetCurSel();
	if (nIndex != CB_ERR)
	{
		CString  strItem;
		mComboTrans.GetLBText(nIndex, strItem);

		CDESTransition  videoTrans(&mTimeLine);
		// Now, mCurrentVideoSource must point to the following video source!!
		// Determine if a transition is already existing
		double timeStart = 0, timeStop = 0;
		mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
		bool pass = mVideoTrackMajor2->GetTransAtTime2(videoTrans, timeStart, DEXTERF_EXACTLY_AT);
		if (!pass && strItem != "None") 
		{
			// If NOT found a existing transition, create a new one
			// And add this new transition to the track
			pass = videoTrans.Initialize();
			pass = mVideoTrackMajor2->TransAdd(videoTrans);
			// Set a default transition
			videoTrans.SetSubObjectGUID(CLSID_DxtJpeg);
			// Change transition direction if necessary
			BOOL  changed = (mCurrentTransNode % 2 == 0) ? TRUE : FALSE;
			videoTrans.SetSwapInputs(changed);
			// Adjust the video source' timeline start time and stop time
			if (timeStart >= TRANS_DURATION) // Overlap the source
			{
				timeStart = timeStart - TRANS_DURATION;
				timeStop  = timeStop - TRANS_DURATION;
				mCurrentVideoSource->SetStartStop2(timeStart, timeStop);
				// Remember to change audio time
				// Be sure not to overlap audio source on the same track
				if (mCurrentAudioSource)
				{
					mCurrentAudioSource->SetStartStop2(timeStart + TRANS_DURATION, timeStop);
					mCurrentAudioSource->SetMediaTimes2(0, timeStop - timeStart - TRANS_DURATION);
				}
				// Remember to adjust effect time
				if (mCurrentVideoEffect)
				{
					mCurrentVideoEffect->SetStartStop2(timeStart, timeStop);
				}
				// Remember to adjust picture in picture time
				ApplyPictureInPicture();
				// Remember to adjust audio mixing time
				ApplyMixingAudio();
			}
			videoTrans.SetStartStop2(timeStart, timeStart + TRANS_DURATION);
		}
		else if (strItem == "None")
		{
			// Delete!!!
			videoTrans.RemoveAll();
			// Adjust timeline time!!
			double timeStart = 0, timeStop = 0;
			mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
			timeStart += TRANS_DURATION;
			timeStop  += TRANS_DURATION;
			mCurrentVideoSource->SetStartStop2(timeStart, timeStop);
			// Remember to change audio time
			// Be sure not to overlap audio source on the same track
			if (mCurrentAudioSource)
			{
				double audioStart, audioStop;
				mCurrentAudioSource->GetMediaTimes2(&audioStart, &audioStop);
				mCurrentAudioSource->SetMediaTimes2(audioStart, audioStop + TRANS_DURATION);
			}
			// Remember to adjust effect time
			if (mCurrentVideoEffect)
			{
				mCurrentVideoEffect->SetStartStop2(timeStart, timeStop);
			}
			// Remember to adjust picture in picture time
			ApplyPictureInPicture();
			// Remember to adjust audio mixing time
			ApplyMixingAudio();

			return;
		}

		// Get the selected GUID and set properties
		CDESGuid   guid;
		POSITION   pos = UDESUtils::sTransitionList.GetHeadPosition();
		while (pos && nIndex >= 0)
		{
			guid = UDESUtils::sTransitionList.GetNext(pos);
			nIndex--;
		}
		// Set subobject guid
		videoTrans.SetSubObjectGUID(guid.mGuid);

		if (guid.mGuid == CLSID_DxtJpeg)
		{
			UpdateData(TRUE);
			CDESPropertySetter   propSetter;
			pass = propSetter.Initialize();
			pass = propSetter.AddProperty(L"MaskNum", mTransTypeValue, TRUE);
			pass = videoTrans.SetPropertySetter(propSetter);
		}
	}
}

void CTestDESDlg::OnButTrans1() 
{
	if (mVideoSources[1]) // The following source must have been added
	{
		UpdateProgressMark(2);
		mCurrentTransNode = 1;

		EnableTransitionSetting(TRUE);
		EnableSourceSetting(FALSE);

		// Be sure to change current videosource and audio source
		mCurrentVideoSource = mVideoSources[1];
		mCurrentAudioSource = mAudioSources[1];
		mCurrentVideoEffect = mVideoEffects[1];
		mCurrentSourceNode  = 2;
	}
}

void CTestDESDlg::OnButTrans2() 
{
	if (mVideoSources[2])
	{
		UpdateProgressMark(4);
		mCurrentTransNode = 2;

		EnableTransitionSetting(TRUE);
		EnableSourceSetting(FALSE);

		// Be sure to change current videosource and audio source
		mCurrentVideoSource = mVideoSources[2];
		mCurrentAudioSource = mAudioSources[2];
		mCurrentVideoEffect = mVideoEffects[2];
		mCurrentSourceNode  = 3;
	}
}

void CTestDESDlg::OnButSrc3() 
{
	// TODO: Add your control notification handler code here
	if (mVideoSources[0] == NULL || mVideoSources[1] == NULL)
		return;

	// Has no valid source file
	if (mVideoSources[2] == NULL)
	{
		CString       fileName;
		if (EnterNewVideoSource(mVideoTrackMajor1, 3, fileName))
		{
			double timeStart = 0, timeStop = 0;
			mVideoTrackMajor2->GetStartStop2(&timeStart, &timeStop);
			// If static image file, set default bps to 0.0
			if (IsImageFile(fileName))
			{
				mCurrentVideoSource->SetStartStop2(timeStop, timeStop + IMAGE_DURATION);
				mCurrentVideoSource->SetMediaTimes2(0, IMAGE_DURATION);
				mCurrentVideoSource->SetDefaultFPS(0);
			}
			else
			{
				double  timeLength = 0;
				mFileDetector.put_Filename(fileName);
				mFileDetector.get_StreamLength(&timeLength);

				mCurrentVideoSource->SetMediaLength2(timeLength);
				mCurrentVideoSource->SetStartStop2(timeStop, timeStop + timeLength);
				mCurrentVideoSource->SetMediaTimes2(0, timeLength);

				// Keep audio syc with video using video track's timeStart and timeStop
				if (mCurrentAudioSource)
				{
					mCurrentAudioSource->SetMediaLength2(timeLength);
					mCurrentAudioSource->SetStartStop2(timeStop, timeStop + timeLength);
					mCurrentAudioSource->SetMediaTimes2(0, timeLength);
				}
			}
		}
	}

	// Switch to property setting pad of the current source
	if (mVideoSources[2])
	{
		UpdateProgressMark(5);

		EnableTransitionSetting(FALSE);
		EnableSourceSetting(TRUE);

		mCurrentSourceNode = 3;
		mCurrentVideoTrack  = mVideoTrackMajor1;
		mCurrentVideoEffect = mVideoEffects[2];
		mCurrentVideoSource = mVideoSources[2];
		mCurrentAudioSource = mAudioSources[2];
		ReflectNewSource(mCurrentVideoSource);

		////////////////////// Pause preview graph ////////////////////////
		PreviewCurrentSource();
		////////////////////////////////////////////////////////////////////
	}
}

void CTestDESDlg::OnButTrans3() 
{
	// TODO: Add your control notification handler code here
	if (mVideoSources[3])
	{
//		UpdateProgressMark(6);
		mCurrentTransNode = 3;
//		EnableTransitionSetting(TRUE);
//		EnableSourceSetting(FALSE);
	}
	
}

void CTestDESDlg::OnButSrc4() 
{
	// TODO: Add your control notification handler code here
	
}

void CTestDESDlg::OnButTrans4() 
{
	// TODO: Add your control notification handler code here
	
}

void CTestDESDlg::OnButSrc5() 
{
	// TODO: Add your control notification handler code here
	
}

/////////////////////// TimeLine preview /////////////////////////////////////
void CTestDESDlg::OnButPreview() 
{
//	bool pass = mRenderEngine.ScrapIt();
//	pass = mRenderEngine.SetTimelineObject(mTimeLine);

	double  timeStart, timeStop;
	mVideoGroup->GetStartStop2(&timeStart, &timeStop);
	mRenderEngine.SetRenderRange2(timeStart, timeStop);
	SeekToTimelinePosition(0);

	BOOL needReset = FALSE;
	if (mRenderEngine.ConnectFrontEnd(&needReset))
	{
		if (needReset)
		{
			mRenderEngine.RenderOutputPins();
			SetVideoWindow();
		}
	}
	
	mRenderEngine.GraphRun();
}

void CTestDESDlg::OnButPlay() 
{
	// TODO: Add your control notification handler code here
//	SeekToTimelinePosition(0);
	mRenderEngine.GraphRun();	
}

void CTestDESDlg::OnButPause() 
{
	// TODO: Add your control notification handler code here
	mRenderEngine.GraphPause();
}

void CTestDESDlg::OnButStop() 
{
	// TODO: Add your control notification handler code here
	mRenderEngine.GraphStop();
	SeekToTimelinePosition(0);
}
//////////////////////////////////////////////////////////////////////////////

void CTestDESDlg::SetVideoWindow(void)
{
	IGraphBuilder * pBuilder = NULL;
	mRenderEngine.GetFilterGraph(&pBuilder);
	if (pBuilder != NULL)
	{
		IVideoWindow *  pVidWindow;
		HRESULT hr = pBuilder->QueryInterface(IID_IVideoWindow, (void**) &pVidWindow);
		if (SUCCEEDED(hr))
		{
			hr = pVidWindow->put_Visible(OAFALSE);
			hr = pVidWindow->put_Owner((OAHWND) mVideoWindow.GetSafeHwnd());
			hr = pVidWindow->put_WindowStyle(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
		
			RECT     windowRect;
			mVideoWindow.GetClientRect(&windowRect);
			pVidWindow->put_Left(0);
			pVidWindow->put_Top(0);
			pVidWindow->put_Width(windowRect.right - windowRect.left);
			pVidWindow->put_Height(windowRect.bottom - windowRect.top);
		
			hr = pVidWindow->put_Visible(OATRUE);

			pVidWindow->Release();
		}
		pBuilder->Release();
	}
}

void CTestDESDlg::SeekToTimelinePosition(double inTimePos)
{
	IGraphBuilder * pBuilder = NULL;
	mRenderEngine.GetFilterGraph(&pBuilder);
	if (pBuilder != NULL)
	{
		IMediaSeeking *  pSeeking;
		HRESULT hr = pBuilder->QueryInterface(IID_IMediaSeeking, (void**) &pSeeking);
		if (SUCCEEDED(hr))
		{
			REFERENCE_TIME Start = REFERENCE_TIME(inTimePos * UNITS);
			hr = pSeeking->SetPositions(&Start, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning );
    		pSeeking->Release();
		}
		pBuilder->Release();
	}
}

void CTestDESDlg::PreviewCurrentSource(void)
{
	mRenderEngine.GraphStop();

	// Render range must be set before ConnectFrontEnd invoking
	double timeStart = 0, timeStop = 0;
	mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
	SeekToTimelinePosition(0);
	mRenderEngine.SetRenderRange2(timeStart, timeStop);
	
	BOOL needReset = FALSE;
	if (mRenderEngine.ConnectFrontEnd(&needReset))
	{
		if (needReset)
		{
			mRenderEngine.RenderOutputPins();
			SetVideoWindow();
		}
	}

	mRenderEngine.GraphPause();	
}

void CTestDESDlg::OnAudioBack() 
{
	// TODO: Add your control notification handler code here
	CString       fileName;
	CString       strFilter = "Mp3 File (*.mp3)|*.mp3|";
	strFilter += "Wave File (*.wav)|*.wav|";
	if (OpenFileDialog(strFilter, fileName))
	{
		CDESSource * pBackAudio = NULL;
		if (AudioBackgroundList.GetCount() == 0)
		{
			pBackAudio = new CDESSource(&mTimeLine);
			bool pass = pBackAudio->Initialize();
			pBackAudio->SetMediaName(fileName);
			AudioBackgroundList.AddTail(pBackAudio);
			pass = mAudioTrackMinor1->SrcAdd(*pBackAudio);
		}
		else
		{
			pBackAudio = (CDESSource *) AudioBackgroundList.GetHead();
		}

		if (pBackAudio) // Set audio source properties
		{
			pBackAudio->SetMediaName(fileName);
			// Determine if a transition is already existing
			double timeStart = 0, timeStop = 0;
			mVideoGroup->GetStartStop2(&timeStart, &timeStop);	
			double  timeLength = 0;
			mFileDetector.put_Filename(fileName);
			mFileDetector.get_StreamLength(&timeLength);

			bool   bLargeSource = (timeStop - timeStart > timeLength);
			double mediaStop = bLargeSource ? timeLength : (timeStop - timeStart);
			pBackAudio->SetMediaTimes2(0, mediaStop);
			pBackAudio->SetStartStop2(timeStart, timeStart + mediaStop);
		}
	}
}



////////////////////////////////// File output ///////////////////////////////////
void CTestDESDlg::OnButSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int nIndex = mSaveFilename.ReverseFind('.');
	if (nIndex != -1)
	{
		mSaveFilename = mSaveFilename.Left(nIndex);
		mSaveFilename = mSaveFilename + ".xtl";
		UpdateData(FALSE);
	}

	CDESXml   xmlSaver;
	if (xmlSaver.Initialize())
	{
		xmlSaver.WriteXMLFile(mTimeLine, mSaveFilename);
		::AfxMessageBox(mSaveFilename + " saved OK!");
	}
}

void CTestDESDlg::OnButtonSavegrf() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int nIndex = mSaveFilename.ReverseFind('.');
	if (nIndex != -1)
	{
		mSaveFilename = mSaveFilename.Left(nIndex);
		mSaveFilename = mSaveFilename + ".grf";
		UpdateData(FALSE);
	}

	CDESXml   grfSaver;
	if (grfSaver.Initialize())
	{
		IGraphBuilder * pBuilder = NULL;
		mRenderEngine.GetFilterGraph(&pBuilder);
		if (pBuilder != NULL)
		{
			grfSaver.WriteGrfFile(pBuilder, mSaveFilename);
			pBuilder->Release();
			::AfxMessageBox(mSaveFilename + " saved OK!");
		}
	}
}

void CTestDESDlg::OnButMux() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	StWaitCursor  stWait;
	int nIndex = mSaveFilename.ReverseFind('.');
	if (nIndex != -1)
	{
		mSaveFilename = mSaveFilename.Left(nIndex);
		mSaveFilename = mSaveFilename + ".avi";
		UpdateData(FALSE);
	}

	mRenderEngine.GraphStop();
	bool pass = mRenderEngine.ScrapIt();
	pass = mRenderEngine.SetTimelineObject(mTimeLine);
	pass = mTimeLine.ValidateSourceNames(); // Validate sources!!
	double  timeStart, timeStop;
	mVideoGroup->GetStartStop2(&timeStart, &timeStop);
	mRenderEngine.SetRenderRange2(timeStart, timeStop);
	SeekToTimelinePosition(0);

	pass = mRenderEngine.ConnectFrontEnd();

	WCHAR    szFilePath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, mSaveFilename, -1, szFilePath, MAX_PATH);
	pass = ConnectOutputFile(szFilePath);

	pass = mRenderEngine.GraphRun();
	pass = mRenderEngine.WaitForCompletion();
	pass = mRenderEngine.GraphStop();

	// Switch to preview mode
	pass = mRenderEngine.ScrapIt();
	pass = mRenderEngine.SetTimelineObject(mTimeLine);

	::AfxMessageBox(mSaveFilename + " saved OK!");
}
///////////////////////////////////////////////////////////////////////////////////




void CTestDESDlg::OnPropApply() 
{
	// Apply start and stop time
	// Apply mixing audio source
	ApplyMixingAudio();
	// Apply picture-in-picture
	ApplyPictureInPicture();
	// Apply video effect and params
	ApplyVideoEffect();

	if (mCurrentVideoSource)
	{
		// Refresh the UI display
		ReflectNewSource(mCurrentVideoSource);
	}
	////////////////////// Pause preview graph ////////////////////////
	PreviewCurrentSource();
	////////////////////////////////////////////////////////////////////
}

void CTestDESDlg::OnTransApply() 
{
	EnterNewTransition();
}

void CTestDESDlg::ApplyMixingAudio(void)
{
	UpdateData(TRUE);

	CDESSource * pAudioMix = mAudioMixings[mCurrentSourceNode - 1];
	if (mMixAudioFilename != "" && pAudioMix == NULL)
	{
		// Create a new pip feature
		// Add the source file to the track
		pAudioMix = new CDESSource(&mTimeLine);
		mAudioMixings[mCurrentSourceNode - 1] = pAudioMix;
		bool pass = pAudioMix->Initialize();
		pass = pAudioMix->SetMediaName(mMixAudioFilename);
		pass = mAudioTrackMajor2->SrcAdd(*pAudioMix);
	}

	// Change new audio mixing file properties
	if (mMixAudioFilename != "" && pAudioMix) 
	{
		pAudioMix->SetMediaName(mMixAudioFilename);

		//////////////////////////////////////////////////////////////////
		double timeStart = 0, timeStop = 0;
		mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
		double preStart, preStop;
		double actualStart = timeStart, actualStop = timeStop;
		// Compare with the previous pip file source
		if (mCurrentSourceNode > 1)
		{
			CDESSource * pSource = mAudioMixings[mCurrentSourceNode - 2];
			if (pSource)
			{
				pSource->GetStartStop2(&preStart, &preStop);
				if (preStop > timeStart)
				{
					actualStart = preStop;
				}
				if (preStop > timeStop)
				{
					// Error
					actualStop = actualStart;
				}
			}
		}
		//////////////////////////////////////////////////////////////////

	    // Determine if a transition is already existing	
		double  timeLength = 0;
		mFileDetector.put_Filename(mMixAudioFilename);
		mFileDetector.get_StreamLength(&timeLength);
		bool   bLargeSource = (actualStop - actualStart > timeLength);
		double mediaStop = bLargeSource ? timeLength : (actualStop - actualStart);
		pAudioMix->SetMediaTimes2(0, mediaStop);
		pAudioMix->SetStartStop2(actualStart, actualStart + mediaStop);
	}
	else if (mMixAudioFilename == "" && pAudioMix) 
	{
		pAudioMix->RemoveAll();
		delete pAudioMix;
		mAudioMixings[mCurrentSourceNode - 1] = NULL;
	}
}

void CTestDESDlg::ApplyPictureInPicture(void)
{
	UpdateData(TRUE);
	
	CDESSource * pPipNode = mPipVideoSources[mCurrentSourceNode - 1];
	if (mPipFilename != "" && pPipNode == NULL)
	{
		// Create a new pip feature
		// Add the source file to the track
		pPipNode = new CDESSource(&mTimeLine);
		mPipVideoSources[mCurrentSourceNode - 1] = pPipNode;
		bool pass = pPipNode->Initialize();
		pass = pPipNode->SetMediaName(mPipFilename);
		pass = mVideoTrackMinor1->SrcAdd(*pPipNode);
		
		// Add whole timeline length compositor transition
	//	CDESTransition  videoTrans(&mTimeLine);
	//	bool found = mVideoTrackMinor1->GetTransAtTime2(videoTrans, 0, DEXTERF_EXACTLY_AT);
		if (mPipTransition == NULL) 
		{
			mPipTransition = new CDESTransition(&mTimeLine);
			mPipTransition->Initialize();
			mPipTransition->SetSubObjectGUID(CLSID_DxtCompositor);
			mVideoTrackMinor1->TransAdd(*mPipTransition);
			// Set propertis
			CDESPropertySetter   propSetter;
			pass = propSetter.Initialize();
			pass = propSetter.AddProperty(L"Width", 80, TRUE);
			pass = propSetter.AddProperty(L"Height", 60, TRUE);
			pass = mPipTransition->SetPropertySetter(propSetter);
		}	
	}

	// Change new pip file properties
	// Not overlap timeline time!!!
	if (mPipFilename != "" && pPipNode && mPipTransition) 
	{
		pPipNode->SetMediaName(mPipFilename);
		//////////////////////////////////////////////////////////////////
		double timeStart = 0, timeStop = 0;
		mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
		double preStart, preStop;
		double actualStart = timeStart, actualStop = timeStop;
		// Compare with the previous pip file source
		if (mCurrentSourceNode > 1)
		{
			CDESSource * pSource = mPipVideoSources[mCurrentSourceNode - 2];
			if (pSource)
			{
				pSource->GetStartStop2(&preStart, &preStop);
				if (preStop > timeStart)
				{
					actualStart = preStop;
				}
				if (preStop > timeStop)
				{
					// Error
					actualStop = actualStart;
				}
			}
		}
		//////////////////////////////////////////////////////////////////

		// If static image file, set default bps to 0.0
		// And set the duration same as the major video source
		if (IsImageFile(mPipFilename))
		{
			pPipNode->SetStartStop2(actualStart, actualStop);
			pPipNode->SetMediaTimes2(0, actualStop);
			pPipNode->SetDefaultFPS(0);
		}
		else
		{
			double  timeLength = 0;
			mFileDetector.put_Filename(mPipFilename);
			mFileDetector.get_StreamLength(&timeLength);
			bool   bLargeSource = (actualStop - actualStart > timeLength);
			double mediaStop = bLargeSource ? timeLength : (actualStop - actualStart);
			pPipNode->SetMediaTimes2(0, mediaStop);
			pPipNode->SetStartStop2(actualStart, actualStart + mediaStop);
		}

		///////////////// Attention!!!!!!
		// Modify transition after modifying source
		// Or you'll never make a pip feature properly!!!
		double videoStart = 0, videoStop = 0;
		mVideoGroup->GetStartStop2(&videoStart, &videoStop);
		mPipTransition->SetStartStop2(videoStart, videoStop);
		////////////////////////////////////////////////////////
	}
	else if (mPipFilename == "" && pPipNode) 
	{
		// Delete Pip feature
	/*	CDESTransition   videoTrans(&mTimeLine);
	    // Determine if a transition is already existing
		double timeStart = 0, timeStop = 0;
		mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
		bool pass = mVideoTrackMinor1->GetTransAtTime2(videoTrans, timeStart, DEXTERF_EXACTLY_AT);
		if (pass)
		{
			videoTrans.RemoveAll();
		}*/

		pPipNode->RemoveAll();
		delete pPipNode;
		mPipVideoSources[mCurrentSourceNode - 1] = NULL;
	}
}

void CTestDESDlg::ApplyVideoEffect(void)
{
	int nIndex = mComboEffects.GetCurSel();
	if (nIndex != CB_ERR && mCurrentVideoTrack)
	{
	//	CDESEffect  videoEffect(&mTimeLine);
	//	long effectCount = 0;
	//	bool pass = mCurrentVideoTrack->EffectGetCount(&effectCount);
	//	if (pass && effectCount > 0)
	//	{
	//		// If an effect already exists, just get it!!
	//		mCurrentVideoTrack->GetEffect(videoEffect, 0);
	//	}
	//	else
		CString  strItem;
		mComboEffects.GetLBText(nIndex, strItem);
		if (strItem == "None")
		{
			// Delete the effect!!
			if (mCurrentSourceNode > 0 && mVideoEffects[mCurrentSourceNode - 1])
			{
				mVideoEffects[mCurrentSourceNode - 1]->RemoveAll();
				delete mVideoEffects[mCurrentSourceNode - 1];
				mVideoEffects[mCurrentSourceNode - 1] = NULL;
				mCurrentVideoEffect = NULL;
			}
			return;
		}
		else if (mCurrentSourceNode > 0 && mVideoEffects[mCurrentSourceNode - 1] == NULL)
		{
			// Insert a new effect
			mCurrentVideoEffect = new CDESEffect(&mTimeLine);
			mVideoEffects[mCurrentSourceNode - 1] = mCurrentVideoEffect;
			bool pass = mCurrentVideoEffect->Initialize();
			pass = mCurrentVideoTrack->EffectInsBefore(*mCurrentVideoEffect, -1);
			double timeStart = 0, timeStop = 0;
			mCurrentVideoSource->GetStartStop2(&timeStart, &timeStop);
			mCurrentVideoEffect->SetStartStop2(timeStart, timeStop);
		}

		// Get currently selected Effect Guid
		
		CDESGuid   guid;
		POSITION   pos = UDESUtils::sEffectList.GetHeadPosition();
		while (pos && nIndex >= 0)
		{
			guid = UDESUtils::sEffectList.GetNext(pos);
			nIndex--;
		}
		mCurrentVideoEffect->SetSubObjectGUID(guid.mGuid);

		// Set properties on the effect object
		ReallySetVideoEffect(*mCurrentVideoEffect, &guid.mGuid);
	}
}

void CTestDESDlg::ReallySetVideoEffect(CDESEffect & inEffect, GUID * inEffectGuid)
{
	UpdateData(TRUE);

	CDESPropertySetter   propSetter;
	bool pass = inEffect.GetPropertySetter(propSetter);
	if (!pass)
	{
		pass = propSetter.Initialize();
		pass = inEffect.SetPropertySetter(propSetter);
	}

	bool    found = false;
	GUID    effectID;
	HRESULT hr    = NOERROR;
	if (!found)
	{
		hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.BasicImage"), &effectID);
		if (SUCCEEDED(hr) && *inEffectGuid == effectID)
		{
			found = true;
			// BasicImage
			pass = propSetter.AddProperty(L"XRay", double(mImageXRay), TRUE);
			pass = propSetter.AddProperty(L"Invert", double(mImageInvert), TRUE);
			pass = propSetter.AddProperty(L"Mirror", double(mImageMirror), TRUE);
			pass = propSetter.AddProperty(L"Grayscale", double(mImageGray), TRUE);
			pass = propSetter.AddProperty(L"Rotation", mImageRotation ? 2 : double(0), TRUE);
			pass = propSetter.AddProperty(L"Opacity", mImageOpacity ? 0.5 : 1.0, TRUE);
		}
	}
	if (!found)
	{
		hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Blur"), &effectID);
		if (SUCCEEDED(hr) && *inEffectGuid == effectID)
		{
			found = true;
			// Blur
			pass = propSetter.AddProperty(L"PixelRadius", 5, TRUE);
			pass = propSetter.AddProperty(L"MakeShadow", double(0), TRUE);
			pass = propSetter.AddProperty(L"ShadowOpacity", 1, TRUE);
		}
	}
	if (!found)
	{
		hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Pixelate"), &effectID);
		if (SUCCEEDED(hr) && *inEffectGuid == effectID)
		{
			found = true;
			// Pixelate
			pass = propSetter.AddProperty(L"maxsquare", 50, TRUE);
		}
	}
	if (!found)
	{
		hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.MotionBlur"), &effectID);
		if (SUCCEEDED(hr) && *inEffectGuid == effectID)
		{
			found = true;
			// MotionBlur
			pass = propSetter.AddProperty(L"Strength", 10, TRUE);
			pass = propSetter.AddProperty(L"Direction", 45, TRUE);
			pass = propSetter.AddProperty(L"Add", 1, TRUE);
		}
	}
	if (!found)
	{
		hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Wave"), &effectID);
		if (SUCCEEDED(hr) && *inEffectGuid == effectID)
		{
			found = true;
			// Wave
			pass = propSetter.AddProperty(L"LightStrength", 100, TRUE);
			pass = propSetter.AddProperty(L"Phase", 30, TRUE);
			pass = propSetter.AddProperty(L"Strength", 5, TRUE);
			pass = propSetter.AddProperty(L"Freq", 9, TRUE);
			pass = propSetter.AddProperty(L"Add", double(0), TRUE);
		}
	}
}

void CTestDESDlg::OnSelchangeTransitions() 
{
	// TODO: Add your control notification handler code here
	ReflectNewTransition();	
}

void CTestDESDlg::OnSelchangeEffects() 
{
	// TODO: Add your control notification handler code here
	ReflectNewEffect();
}

void CTestDESDlg::ReflectNewEffect(void)
{
	int nIndex = mComboEffects.GetCurSel();
	if (nIndex != CB_ERR)
	{
		// Get the selected GUID
		CDESGuid   guid;
		POSITION   pos = UDESUtils::sEffectList.GetHeadPosition();
		while (pos && nIndex >= 0)
		{
			guid = UDESUtils::sEffectList.GetNext(pos);
			nIndex--;
		}

		GUID    effectID;
		CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.BasicImage"), &effectID);
		// Determine SMPTE CLSID_DxtJpeg
		if (guid.mGuid == effectID)
		{
			ShowBasicImageEffectDetails(TRUE);
		}
		else
		{
			ShowBasicImageEffectDetails(FALSE);
		}
	}
}

void CTestDESDlg::ReflectNewTransition(void)
{
	int nIndex = mComboTrans.GetCurSel();
	if (nIndex != CB_ERR)
	{	
		// Get the selected GUID
		CDESGuid   guid;
		POSITION   pos = UDESUtils::sTransitionList.GetHeadPosition();
		while (pos && nIndex >= 0)
		{
			guid = UDESUtils::sTransitionList.GetNext(pos);
			nIndex--;
		}

		// Determine SMPTE CLSID_DxtJpeg
		if (guid.mGuid == CLSID_DxtJpeg)
		{
			mTransType.ShowWindow(TRUE);
			mTransTitleType.ShowWindow(TRUE);
		}
		else
		{
			mTransType.ShowWindow(FALSE);
			mTransTitleType.ShowWindow(FALSE);
		}
	}
}

void CTestDESDlg::EnableTransitionSetting(BOOL inEnable)
{
	mTransType.EnableWindow(inEnable);
	mComboTrans.EnableWindow(inEnable);
	mTransApply.EnableWindow(inEnable);
//	mTitleTrans.EnableWindow(inEnable);
//	mFrameTrans.EnableWindow(inEnable);
}

void CTestDESDlg::EnableSourceSetting(BOOL inEnable)
{
	mComboEffects.EnableWindow(inEnable);
	mPropApply.EnableWindow(inEnable);
	mVideoSourceBrowser.EnableWindow(inEnable);
	mAudioMixFileBrowser.EnableWindow(inEnable);
	mPipFileBrowser.EnableWindow(inEnable);
}

void CTestDESDlg::ShowBasicImageEffectDetails(BOOL inEnable)
{
	GetDlgItem(IDC_IMGAE_XRAY)->ShowWindow(inEnable);
	GetDlgItem(IDC_IMGAE_MIRROR)->ShowWindow(inEnable);
	GetDlgItem(IDC_IMGAE_GRAY)->ShowWindow(inEnable);
	GetDlgItem(IDC_IMGAE_INVERT)->ShowWindow(inEnable);
	GetDlgItem(IDC_IMGAE_ROTATION)->ShowWindow(inEnable);
	GetDlgItem(IDC_IMGAE_OPACITY)->ShowWindow(inEnable);
}

void CTestDESDlg::UpdateProgressMark(int inProgress)
{
	int ProgressIDs[] = 
	{
		IDC_STATIC_STATUS1,
		IDC_STATIC_STATUS2,
		IDC_STATIC_STATUS3,
		IDC_STATIC_STATUS4,
		IDC_STATIC_STATUS5,
		IDC_STATIC_STATUS6,
		IDC_STATIC_STATUS7,
		IDC_STATIC_STATUS8,
		IDC_STATIC_STATUS9
	};
	int nCount = sizeof(ProgressIDs) / sizeof(ProgressIDs[0]);

	for (int i = 0; i < nCount; i++)
	{
		GetDlgItem(ProgressIDs[i])->SetWindowText("");
	}
	GetDlgItem(ProgressIDs[inProgress - 1])->SetWindowText("*****");
}






//
// Configure the graph to write to an AVI file
//
bool CTestDESDlg::ConnectOutputFile(WCHAR * inFilename)
{
	IGraphBuilder * pGraph = NULL;
	IBaseFilter * pMux = NULL;
    IFileSinkFilter * pWriter = NULL;
    ICaptureGraphBuilder2 * pBuilder = NULL;
	HRESULT hr = CoCreateInstance(CLSID_CaptureGraphBuilder2,
									NULL,
									CLSCTX_INPROC_SERVER,
									IID_ICaptureGraphBuilder2,
									(void**) &pBuilder );
	bool pass = SUCCEEDED(hr) ? true : false;
	if (pass)
	{
		pass = mRenderEngine.GetFilterGraph(&pGraph);
	}
	if (pass)
	{
		hr = pBuilder->SetFiltergraph(pGraph);
		pass = SUCCEEDED(hr) ? true : false;
	}
	if (pass)
	{
		GUID guid = MEDIASUBTYPE_Avi;
		hr = pBuilder->SetOutputFileName(&guid, inFilename, &pMux, &pWriter );
		pass = SUCCEEDED(hr) ? true : false;
	}
	if (pass)
	{
		// Setting on mux
		IConfigInterleaving * pConfigInterleaving = NULL;
		pMux->QueryInterface(IID_IConfigInterleaving, (void **) &pConfigInterleaving);
		if (pConfigInterleaving) 
		{
			pConfigInterleaving->put_Mode(INTERLEAVE_FULL);
			pConfigInterleaving->Release();
		}
		// Setting on file writer
		IFileSinkFilter2 *  pCfgFw = NULL;
		pWriter->QueryInterface(IID_IFileSinkFilter2, (void **) &pCfgFw);
		if (pCfgFw) 
		{
			pCfgFw->SetMode(AM_FILE_OVERWRITE);
			pCfgFw->Release();
		}

		// Finish to connection
		long   Groups = mTimeLine.GetGroupCount();
		for (int g = 0 ; g < Groups ; g++)
		{
			IPin * pPin = NULL;
			mRenderEngine.GetGroupOutputPin(g, &pPin);
			if (pPin != NULL)
			{
				pBuilder->RenderStream(NULL, NULL, pPin, NULL, pMux);
				pPin->Release();
			}
		}
	}

    // Release interfaces
    if (pGraph)
	{
		pGraph->Release();
	}
	if (pMux)
	{
		pMux->Release();
	}
	if (pWriter)
	{
		pWriter->Release();
	}
	if (pBuilder)
	{
		pBuilder->Release();
	}
    return pass;
}
////////////////////////////////////////////////////////////////////////////////











/*
void CTestDESDlg::ApplyVideoEffect(void)
{
	if (mCurrentVideoSource)
	{
		CDESEffect  videoEffect(&mTimeLine);
		bool pass = videoEffect.Initialize();
		GUID    effectID;
		HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.BasicImage"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Alpha"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.AlphaImageLoader"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Blur"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Chroma"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.dropShadow"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Emboss"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Engrave"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Pixelate"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.MotionBlur"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Wave"), &effectID);
	//	HRESULT hr = CLSIDFromProgID(OLESTR("DXImageTransform.Microsoft.Shadow"), &effectID);
		videoEffect.SetSubObjectGUID(effectID);

		double timeStart, timeStop;
		mCurrentVideoSource->GetMediaTimes2(&timeStart, &timeStop);
		videoEffect.SetStartStop2(timeStart, timeStop);

		pass = mCurrentVideoSource->EffectInsBefore(videoEffect, -1);

		CDESPropertySetter   propSetter;
		pass = propSetter.Initialize();

		// Alpha // ?
	/*	pass = propSetter.AddProperty(L"Style", 2, TRUE);
		pass = propSetter.AddProperty(L"Opacity", 100, TRUE);
		pass = propSetter.AddProperty(L"FinishOpacity", 0, TRUE);*/

		// AlphaImageLoader // ?
	/*	pass = propSetter.AddProperty(L"src", L"MOUSE2.GIF", TRUE);
		pass = propSetter.AddProperty(L"sizingmethod", L"scale", TRUE);*/

		// BasicImage
/*		pass = propSetter.AddProperty(L"XRay", double(0), TRUE);
		pass = propSetter.AddProperty(L"Invert", 1, TRUE);
		pass = propSetter.AddProperty(L"Mirror", double(0), TRUE);
		pass = propSetter.AddProperty(L"Grayscale", double(0), TRUE);
		pass = propSetter.AddProperty(L"Rotation", 2, TRUE);
		pass = propSetter.AddProperty(L"Opacity", 0.5, TRUE);

		// Blur
	/*	pass = propSetter.AddProperty(L"PixelRadius", 5, TRUE);
		pass = propSetter.AddProperty(L"MakeShadow", 0, TRUE);
		pass = propSetter.AddProperty(L"ShadowOpacity", 1, TRUE);*/

		// Chroma // ?
	//	pass = propSetter.AddProperty(L"Color", 0xffff00, TRUE);

		// dropShadow // ?
	/*	pass = propSetter.AddProperty(L"Color", 0x0000ff, TRUE);
		pass = propSetter.AddProperty(L"offX", 5, TRUE);
		pass = propSetter.AddProperty(L"offY", 5, TRUE);
		pass = propSetter.AddProperty(L"positive", 1, TRUE);*/

		// Pixelate
	//	pass = propSetter.AddProperty(L"maxsquare", 50, TRUE);

		// MotionBlur
	/*	pass = propSetter.AddProperty(L"Strength", 10, TRUE);
		pass = propSetter.AddProperty(L"Direction", 45, TRUE);
		pass = propSetter.AddProperty(L"Add", 1, TRUE);*/

		// Wave
	/*	pass = propSetter.AddProperty(L"LightStrength", 100, TRUE);
		pass = propSetter.AddProperty(L"Phase", 30, TRUE);
		pass = propSetter.AddProperty(L"Strength", 5, TRUE);
		pass = propSetter.AddProperty(L"Freq", 9, TRUE);
		pass = propSetter.AddProperty(L"Add", double(0), TRUE);*/

		// Shadow // ?
	/*	pass = propSetter.AddProperty(L"color", L"Red", TRUE);
		pass = propSetter.AddProperty(L"Direction", 135, TRUE);
		pass = propSetter.AddProperty(L"Strength", 32, TRUE);*/

/*		pass = videoEffect.SetPropertySetter(propSetter);
	//	bool pass = mCurrentVideoSource->GetPropertySetter(propSetter);		
	}
}
*/

void CTestDESDlg::OnButtonPipfile() 
{
	// TODO: Add your control notification handler code here
	CString       filename;
	CString       strFilter = "Avi File (*.avi)|*.avi|";
	strFilter += "Mpeg File (*.mpg;*.mpeg)|*.mpg;*.mpeg|";
	strFilter += "Image File (*.bmp;*.jpg;*.jpeg;*.gif;*.tga)|*.bmp;*.jpg;*.jpeg;*.gif;*.tga|";
	if (OpenFileDialog(strFilter, filename))
	{
		mPipFilename = filename;
		UpdateData(FALSE);
	}
}

void CTestDESDlg::OnButtonAudioMix() 
{
	// TODO: Add your control notification handler code here
	CString       filename;
	CString       strFilter = "Mp3 File (*.mp3)|*.mp3|";
	strFilter += "Wave File (*.wav)|*.wav|";
	if (OpenFileDialog(strFilter, filename))
	{
		mMixAudioFilename = filename;
		UpdateData(FALSE);
	}
}

bool CTestDESDlg::IsImageFile(CString & inFilename)
{
	int nIndex = inFilename.ReverseFind('.');
	if (nIndex != -1)
	{
		CString  strExt = inFilename.Right(inFilename.GetLength() - nIndex);
		if (strExt.CompareNoCase(".bmp") == 0 ||
			strExt.CompareNoCase(".jpg") == 0 ||
			strExt.CompareNoCase(".jpeg") == 0 ||
			strExt.CompareNoCase(".gif") == 0 ||
			strExt.CompareNoCase(".tga") == 0)
		{
			return true;
		}
	}
	return false;
}

void CTestDESDlg::OnButtonHelp() 
{
	// TODO: Add your control notification handler code here
	CHelpDlg   dlg;
	dlg.DoModal();
}
