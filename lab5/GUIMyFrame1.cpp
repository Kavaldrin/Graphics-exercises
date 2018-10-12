#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>



std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}


void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


void GUIMyFrame1::Repaint()
{
	wxClientDC dc(WxPanel);
	dc.SetBackground(*wxWHITE_BRUSH);
	wxBufferedDC buffered(&dc);
	buffered.Clear();

	wxSize size = WxPanel->GetClientSize();

	double w = size.GetX();
	double h = size.GetY();

	//przeksztalcenia
	Matrix4 t1,t2;
	t1 =Translacja((WxSB_TranslationX->GetValue() - 100.0) / 50.0, (WxSB_TranslationY->GetValue() - 100.0) / 50.0,
		(WxSB_TranslationZ->GetValue() - 100.0) / 50.0)
		*RotacjaX(-WxSB_RotateX->GetValue() * M_PI / 180.0)
		*RotacjaY(-WxSB_RotateY->GetValue() * M_PI / 180.0)
		*RotacjaZ(-WxSB_RotateZ->GetValue() * M_PI / 180.0)
		*Skalowanie(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0,
			WxSB_ScaleZ->GetValue() / 100.0);
	t2 = Dopasuj(w, h)*Perspektywa();

	drawShape(t1,t2,&buffered);

}

void GUIMyFrame1::drawShape(Matrix4 &t1,Matrix4 &t2,wxDC *dc)
{
	

	for (auto &seg : data) {
		dc->SetPen(wxPen(wxColor(seg.color.R, seg.color.G, seg.color.B)));
		line2d(dc,t1,t2,seg.begin,seg.end);
	}

}

void GUIMyFrame1::line2d(wxDC *dc, Matrix4 &t1, Matrix4 &t2, Point &p1, Point &p2)
{
	Vector4 v1;
	v1.Set(p1.x, p1.y, p1.z);
	Vector4 v2;
	v2.Set(p2.x, p2.y, p2.z);

	v1 = t1 * v1;
	v2 = t1 * v2;
	Normalizuj(v1);
	Normalizuj(v2);
	typuCohen(v1, v2,t2);

	dc->DrawLine(v1.GetX(), v1.GetY(), v2.GetX(), v2.GetY());
}

Matrix4 GUIMyFrame1::Perspektywa()
{

	Matrix4 m;

	m.data[0][0] = 1;
	m.data[1][1] = 1;
	m.data[3][2] = 1. / 2.;

	return m;
}

Matrix4 GUIMyFrame1::Dopasuj(double w, double h)
{
	Matrix4 m;
	m.data[0][0] = w/ 2;
	m.data[1][1] = -h/ 2;
	m.data[2][2] = h / 2;
	m.data[0][3] = w/2;
	m.data[1][3] = h/2;


	return m;
}



Matrix4 GUIMyFrame1::Translacja(double x, double y, double z)
{
	Matrix4 m;
	m.data[0][0] = 1.0;
	m.data[1][1] = 1.0;
	m.data[2][2] = 1.0;
	m.data[0][3] = x;
	m.data[1][3] = y;
	m.data[2][3] = z;

	return m;
}
Matrix4 GUIMyFrame1::RotacjaX(double kat)
{
	Matrix4 m;
	m.data[0][0] = 1.0;
	m.data[1][1] = cos(kat);
	m.data[2][1] = sin(kat);
	m.data[1][2] = -sin(kat);
	m.data[2][2] = cos(kat);

	return m;
}
Matrix4 GUIMyFrame1::RotacjaY(double kat)
{
	Matrix4 m;
	m.data[0][0] = cos(kat);
	m.data[0][2] = sin(kat);
	m.data[1][1] = 1.0;
	m.data[2][0] = -sin(kat);
	m.data[2][2] = cos(kat);
	

	return m;
}

Matrix4 GUIMyFrame1::RotacjaZ(double kat)
{
	Matrix4 m;
	m.data[0][0] = cos(kat);
	m.data[0][1] = -sin(kat);
	m.data[1][0] = sin(kat);
	m.data[1][1] = cos(kat);
	m.data[2][2] = 1.0;

	return m;
}

Matrix4 GUIMyFrame1::Skalowanie(double x,double y,double z)
{
	Matrix4 m;

	m.data[0][0] = x;
	m.data[1][1] = y;
	m.data[2][2] = z;
	return m;

}
void GUIMyFrame1::Normalizuj(Vector4 &vec)
{
	vec.data[0] /= vec.data[3];
	vec.data[1] /= vec.data[3];
	vec.data[2] /= vec.data[3];
}

void GUIMyFrame1::typuCohen(Vector4 &v1, Vector4 &v2,Matrix4 &t2)
{
	int granica = -2;

	//jesli jeden z punktow znajduje sie w, a drugi poza
	if (v1.GetZ() > granica && v2.GetZ() <= granica || v2.GetZ() > granica && v1.GetZ() <= granica) {
		Vector4 vec1; // ten poza rysunkiem
		Vector4 vec2; // ten w rysunku

		if (v1.GetZ() <= granica) {
			vec1 = v1;
			vec2 = v2;
		}
		else if (v2.GetZ() <= granica) {
			vec1 = v2;
			vec2 = v1;
		}

		double stosunek = abs((granica - vec1.GetZ()) / (vec2.GetZ() - vec1.GetZ()));

		vec1.data[0] = (vec2.GetX() - vec1.GetX()) * stosunek + vec1.GetX();
		vec1.data[1] = (vec2.GetY() - vec1.GetY()) * stosunek + vec1.GetY();
		vec1.data[2] = granica;

		v1 = t2 * vec1;
		v2 = t2 * vec2;


		Normalizuj(v1);
		Normalizuj(v2);
	}
	//jesli oba w rysunku, nic nie obcinamy
	else if (v1.GetZ() >= granica && v2.GetZ() >= granica) {
		v1 = t2*v1;
		v2 = t2 *v2;
		Normalizuj(v1);
		Normalizuj(v2);
	}
}

///
