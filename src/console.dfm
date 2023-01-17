object ConsoleFrm: TConsoleFrm
  Left = 231
  Top = 763
  Width = 424
  Height = 186
  BorderIcons = [biSystemMenu]
  Caption = 'S.M.F.E. Console'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  Position = poMainFormCenter
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 106
  TextHeight = 13
  object Console: TMemo
    Left = 0
    Top = 0
    Width = 416
    Height = 157
    Align = alClient
    Color = clInfoBk
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
    WordWrap = False
  end
  object PopupMenu1: TPopupMenu
    Left = 336
    Top = 16
    object Copy1: TMenuItem
      Caption = '&Copy'
      OnClick = Copy1Click
    end
    object SelectAll: TMenuItem
      Caption = 'Select &All'
      OnClick = SelectAllClick
    end
    object Clear1: TMenuItem
      Caption = 'Clear'
      OnClick = Clear1Click
    end
  end
end
