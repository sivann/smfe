object AboutFrm: TAboutFrm
  Left = 198
  Top = 458
  Anchors = []
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'About S.M.F.E.'
  ClientHeight = 142
  ClientWidth = 267
  Color = 12639424
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 106
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 248
    Height = 16
    Caption = 'S.M.F.E. - Simple M.A.M.E. Frontend'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 96
    Width = 67
    Height = 39
    Caption = 'Version 0.9'#13#10'30/Sep/2004'#13#10'for mame 0.83'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 16
    Top = 40
    Width = 216
    Height = 39
    Caption = 
      'This Software is FREEWARE'#13#10'(c) Spiros Ioannou'#13#10'http://www.softla' +
      'b.ece.ntua.gr/~sivann/smfe'
  end
  object BitBtn1: TBitBtn
    Left = 192
    Top = 112
    Width = 65
    Height = 25
    Caption = 'Close'
    ModalResult = 1
    TabOrder = 0
  end
end
