object LegendFrm: TLegendFrm
  Left = 250
  Top = 800
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  Caption = 'Icon Legend'
  ClientHeight = 184
  ClientWidth = 167
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Image0: TImage
    Left = 12
    Top = 9
    Width = 25
    Height = 25
    Center = True
    Transparent = True
  end
  object Image1: TImage
    Left = 12
    Top = 41
    Width = 25
    Height = 25
    Center = True
    Transparent = True
  end
  object Image2: TImage
    Left = 12
    Top = 73
    Width = 25
    Height = 25
    Center = True
    Transparent = True
  end
  object Image3: TImage
    Left = 12
    Top = 105
    Width = 25
    Height = 25
    Center = True
    Transparent = True
  end
  object Label1: TLabel
    Left = 49
    Top = 9
    Width = 108
    Height = 26
    Caption = 'ROM found on system and is good'
    WordWrap = True
  end
  object Label2: TLabel
    Left = 49
    Top = 49
    Width = 73
    Height = 13
    Caption = 'ROM not found'
    WordWrap = True
  end
  object Label3: TLabel
    Left = 49
    Top = 73
    Width = 94
    Height = 26
    Caption = 'ROM found but it is not working'
    WordWrap = True
  end
  object Label4: TLabel
    Left = 49
    Top = 105
    Width = 104
    Height = 26
    Caption = 'ROM found and is the best available'
    WordWrap = True
  end
  object Image4: TImage
    Left = 12
    Top = 137
    Width = 25
    Height = 25
    Center = True
    Transparent = True
  end
  object Label5: TLabel
    Left = 49
    Top = 137
    Width = 97
    Height = 26
    Caption = 'ROM exists but is of unknown condition'
    WordWrap = True
  end
end
