#include "stdafx.h"
#include "app.h"
#include "frame.h"
#include "viewLeft.h"
#include "viewRight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(frame, CFrameWnd)

BEGIN_MESSAGE_MAP(frame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &frame::OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, &frame::OnViewStyle)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

frame::frame() { /*TODO: add member initialization code here*/ }

frame::~frame() {}

int frame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL frame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext) {
	if (!m_wndSplitter.CreateStatic(this, 1, 2)) return FALSE; // create splitter window
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(viewLeft), CSize(200, 100), pContext) || //Windows Explorer Application - 31. To give more room to the list tree, access the OnCreateClient and change the width of the left frame as follows. @ http://www.functionx.com/visualc/applications/explorer.htm
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(viewRight), CSize(100, 100), pContext)) 
	{ 
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	return TRUE;
}

BOOL frame::PreCreateWindow(CREATESTRUCT& cs) {
	if (!CFrameWnd::PreCreateWindow(cs)) return FALSE;
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	return TRUE;
}

#ifdef _DEBUG // frame diagnostics
	void frame::AssertValid() const { CFrameWnd::AssertValid(); }
	void frame::Dump(CDumpContext& dc) const { CFrameWnd::Dump(dc); }
#endif

viewRight* frame::GetRightPane() { // frame message handlers
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	viewRight* pView = DYNAMIC_DOWNCAST(viewRight, pWnd);
	return pView;
}

void frame::OnUpdateViewStyles(CCmdUI* pCmdUI) {
	if (!pCmdUI)
		return;

	// TODO: customize or extend this code to handle choices on the View menu

	viewRight* pView = GetRightPane();

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}

void frame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the View menu
	viewRight* pView = GetRightPane();

	// if the right-hand pane has been created and is a viewRight,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle = -1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				CListCtrl& refListCtrl = pView->GetListCtrl();
				refListCtrl.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}

