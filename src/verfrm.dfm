object VerForm: TVerForm
  Left = 321
  Top = 120
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'SMFE - ROM Verify'
  ClientHeight = 134
  ClientWidth = 228
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 106
  TextHeight = 13
  object Label1: TLabel
    Left = 10
    Top = 32
    Width = 177
    Height = 13
    Caption = '1. checking rom availability (5-10 sec)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 10
    Top = 56
    Width = 76
    Height = 13
    Caption = '2. verifying roms'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Labeltit: TLabel
    Left = 8
    Top = 8
    Width = 81
    Height = 13
    Caption = 'Please Wait...'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 10
    Top = 80
    Width = 79
    Height = 13
    Caption = '3. updating table'
  end
  object ProgressBar: TProgressBar
    Left = 0
    Top = 118
    Width = 228
    Height = 16
    Align = alBottom
    Min = 0
    Max = 4000
    TabOrder = 0
  end
end
