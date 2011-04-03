// TestDESDlg.h : header file
//

#if !defined(AFX_TESTDESDLG_H__D3E3E0F1_3A82_4C22_B5F9_29642C333906__INCLUDED_)
#define AFX_TESTDESDLG_H__D3E3E0F1_3A82_4C22_B5F9_29642C333906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDESDlg dialog

#include "CDESTimeLine.h"
#include "CDESGroup.h"
#include "CDESTrack.h"
#include "CDESSource.h"
#include "CDESRenderEngine.h"
#include "CDESMediaDetector.h"
#include "UDESUtils.h"
#include "CDESEffect.h"
#include "CDESTransition.h"

#define MAX_SRC            20
#define TRANS_DURATION     3
#define IMAGE_DURATION     6

class CTestDESDlg : public CDialog
{
// Construction
public:
	CTestDESDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDESDlg)
	enum { IDD = IDD_TESTDES_DIALOG };
	CButton	mPipFileBrowser;
	CButton	mVideoSourceBrowser;
	CButton	mAudioMixFileBrowser;
	CEdit	mTransType;
	CStatic	mTransTitleType;
	CButton	mPropApply;
	CButton	mFrameTrans;
	CStatic	mTitleTrans;
	CButton	mTransApply;
	CStatic	mVideoWindow;
	CComboBox	mComboTrans;
	CComboBox	mComboEffects;
	double	mTimelineStartTime;
	double	mTimelineStopTime;
	CString	mSaveFilename;
	double	mMediaStartTime;
	double	mMediaStopTime;
	int		mTransTypeValue;
	CString	mMixAudioFilename;
	CString	mVideoSrcFile;
	double	mEffectStartTime;
	double	mEffectStopTime;
	CString	mPipFilename;
	BOOL	mImageGray;
	BOOL	mImageInvert;
	BOOL	mImageMirror;
	BOOL	mImageXRay;
	BOOL	mImageRotation;
	BOOL	mImageOpacity;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDESDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON      m_hIcon;

	CDESTimeLine      mTimeLine;
	CDESGroup *       mVideoGroup;
	CDESGroup *       mAudioGroup;
	CDESTrack *       mVideoTrackMajor1;  // The first source track
	CDESTrack *       mVideoTrackMajor2;  // The second source track (can add transition)
	CDESTrack *       mVideoTrackMinor1;  // The third track (can add pip)

	CDESTrack *       mAudioTrackMajor1;  // The track contain original audio
	CDESTrack *       mAudioTrackMajor2;  // The track contain mixing audio with the original audio
	CDESTrack *       mAudioTrackMinor1;  // The track contain the whole background music

	CDESMediaDetector mFileDetector;
	CDESRenderEngine  mRenderEngine;

	CDESTrack *       mCurrentVideoTrack;
	CDESSource *      mCurrentVideoSource;
	CDESSource *      mCurrentAudioSource;
	CDESEffect *      mCurrentVideoEffect;

//	CTypedPtrList <CPtrList, CDESSource *> VideoSourceList;
//	CTypedPtrList <CPtrList, CDESSource *> AudioSourceList;
	CDESSource *      mVideoSources[MAX_SRC];
	CDESSource *      mAudioSources[MAX_SRC];
	CDESEffect *      mVideoEffects[MAX_SRC];
	CDESSource *      mAudioMixings[MAX_SRC];
	CDESSource *      mPipVideoSources[MAX_SRC];
	CDESTransition *  mPipTransition;
	CTypedPtrList <CPtrList, CDESSource *> AudioBackgroundList;
	
	int               mCurrentTransNode;  // 1 based index
	int               mCurrentSourceNode; // 1 based index

private:
	void Init(void);
	void Uninit(void);

	void FillEffectComboBox(void);
	void FillTransitionComboBox(void);

	bool OpenFileDialog(CString & inFilter, CString & outFileName);
	bool EnterNewVideoSource(CDESTrack * inTargetTrack, int inSourceIndex, CString & outFileName);
	
	void ApplyVideoEffect(void);
	void ReallySetVideoEffect(CDESEffect & inEffect, GUID * inEffectGuid);
	void ApplyPictureInPicture(void);
	void ApplyMixingAudio(void);

	void EnableTransitionSetting(BOOL inEnable);
	void EnableSourceSetting(BOOL inEnable);
	void ShowBasicImageEffectDetails(BOOL inEnable);

	void EnterNewTransition(void);
	void EnterSubObjectGuid(void);
	void EnterTransitionProp(GUID * inGuid);

	bool ConnectOutputFile(WCHAR * inFilename);
	bool IsImageFile(CString & inFilename);

	void SetVideoWindow(void);
	void SeekToTimelinePosition(double inTimePos);
	void PreviewCurrentSource(void);

	void ReflectNewSource(CDESSource * inSource);
	void ReflectNewTransition(void);
	void ReflectNewEffect(void);

	void UpdateProgressMark(int inProgress);

	// Generated message map functions
	//{{AFX_MSG(CTestDESDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButSrc1();
	afx_msg void OnPropApply();
	afx_msg void OnButSrc2();
	afx_msg void OnButTrans1();
	afx_msg void OnButPreview();
	afx_msg void OnButPlay();
	afx_msg void OnButPause();
	afx_msg void OnButStop();
	afx_msg void OnAudioBack();
	afx_msg void OnButSave();
	afx_msg void OnButMux();
	afx_msg void OnButTrans2();
	afx_msg void OnButSrc3();
	afx_msg void OnButTrans3();
	afx_msg void OnButSrc4();
	afx_msg void OnButTrans4();
	afx_msg void OnButSrc5();
	afx_msg void OnSelchangeTransitions();
	afx_msg void OnSelchangeEffects();
	afx_msg void OnButtonSavegrf();
	afx_msg void OnTransApply();
	afx_msg void OnButtonPipfile();
	afx_msg void OnButtonAudioMix();
	afx_msg void OnButtonHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDESDLG_H__D3E3E0F1_3A82_4C22_B5F9_29642C333906__INCLUDED_)
