object SettingsFrm: TSettingsFrm
  Left = 260
  Top = 532
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'S.M.F.E. Settings'
  ClientHeight = 388
  ClientWidth = 374
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 8
    Top = 328
    Width = 162
    Height = 26
    Caption = 'Note: only the "Mame Executable Location" is mandatory'
    WordWrap = True
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 361
    Height = 81
    Caption = 'Mame Executable  Location'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 40
      Width = 319
      Height = 26
      Caption = 
        'example: c:\mame\mame.exe  '#13#10'UNC paths are also allowed.E.g.\\ho' +
        'stname\sharename\mame.exe'
    end
    object MLocationEdit: TEdit
      Left = 8
      Top = 16
      Width = 345
      Height = 21
      TabOrder = 0
    end
  end
  object SOkBtn: TBitBtn
    Left = 288
    Top = 360
    Width = 75
    Height = 25
    Caption = 'Close && &Save'
    Default = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = SOkBtnClick
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 96
    Width = 361
    Height = 121
    Caption = 'Fullpath Image locations'
    TabOrder = 1
    object ArtworkEdt: TEdit
      Left = 8
      Top = 16
      Width = 241
      Height = 21
      TabOrder = 0
    end
    object CabinetEdt: TEdit
      Left = 8
      Top = 40
      Width = 241
      Height = 21
      TabOrder = 1
    end
    object FlyerEdt: TEdit
      Left = 8
      Top = 64
      Width = 241
      Height = 21
      TabOrder = 2
    end
    object SnapshotEdt: TEdit
      Left = 8
      Top = 88
      Width = 241
      Height = 21
      TabOrder = 3
    end
    object StaticText1: TStaticText
      Left = 256
      Top = 16
      Width = 85
      Height = 17
      Caption = 'Artwork Directory'
      TabOrder = 4
    end
    object StaticText2: TStaticText
      Left = 256
      Top = 40
      Width = 85
      Height = 17
      Caption = 'Cabinet Directory'
      TabOrder = 5
    end
    object StaticText3: TStaticText
      Left = 256
      Top = 64
      Width = 71
      Height = 17
      Caption = 'Flyer Directory'
      TabOrder = 6
    end
    object StaticText4: TStaticText
      Left = 256
      Top = 88
      Width = 94
      Height = 17
      Caption = 'Snapshot Directory'
      TabOrder = 7
    end
  end
  object SCancelBtn: TBitBtn
    Left = 208
    Top = 360
    Width = 75
    Height = 25
    Caption = 'Close'
    ModalResult = 2
    TabOrder = 6
  end
  object AutoExtract: TCheckBox
    Left = 208
    Top = 328
    Width = 145
    Height = 17
    Caption = 'Refresh gamelist at startup'
    TabOrder = 4
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 224
    Width = 361
    Height = 41
    Caption = 'Search For:'
    TabOrder = 2
    object png: TCheckBox
      Left = 8
      Top = 16
      Width = 41
      Height = 17
      Caption = '.png'
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object jpg: TCheckBox
      Left = 64
      Top = 16
      Width = 57
      Height = 17
      Caption = '.jpg'
      Checked = True
      State = cbChecked
      TabOrder = 1
    end
    object gif: TCheckBox
      Left = 168
      Top = 16
      Width = 41
      Height = 17
      Caption = '.gif'
      TabOrder = 2
    end
    object bmp: TCheckBox
      Left = 216
      Top = 16
      Width = 49
      Height = 17
      Caption = '.bmp'
      TabOrder = 3
    end
    object tif: TCheckBox
      Left = 120
      Top = 16
      Width = 41
      Height = 17
      Caption = '.tif'
      TabOrder = 4
    end
    object ico: TCheckBox
      Left = 272
      Top = 16
      Width = 41
      Height = 17
      Caption = '.ico'
      TabOrder = 5
    end
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 272
    Width = 361
    Height = 49
    Caption = 'History.dat Location'
    TabOrder = 3
    object HistEdt: TEdit
      Left = 8
      Top = 16
      Width = 345
      Height = 21
      TabOrder = 0
      OnEnter = HistEdtEnter
    end
  end
  object AutoFillBtn: TBitBtn
    Left = 8
    Top = 360
    Width = 113
    Height = 25
    Caption = 'Auto Fill'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 7
    OnClick = AutoFillBtnClick
  end
end
