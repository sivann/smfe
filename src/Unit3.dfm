object MAMEOpts: TMAMEOpts
  Left = 198
  Top = 211
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'MAME Options'
  ClientHeight = 414
  ClientWidth = 411
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 106
  TextHeight = 13
  object Edit2: TEdit
    Left = 96
    Top = 96
    Width = 121
    Height = 21
    TabOrder = 1
    Text = 'Edit1'
  end
  object CheckBox2: TCheckBox
    Left = 240
    Top = 96
    Width = 97
    Height = 17
    Caption = 'Use this Setting'
    TabOrder = 2
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 411
    Height = 369
    ActivePage = TabSheet4
    Align = alTop
    HotTrack = True
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Path and Directories'
      object GroupBox9: TGroupBox
        Left = 8
        Top = 128
        Width = 345
        Height = 89
        Caption = 'Snapshots'
        TabOrder = 0
        object Label3: TLabel
          Left = 8
          Top = 32
          Width = 90
          Height = 13
          Caption = 'Snapshot Directory'
        end
        object snapuse: TCheckBox
          Left = 8
          Top = 56
          Width = 225
          Height = 17
          Caption = 'Use this instead of default "snap"'
          TabOrder = 0
        end
        object snapshot: TEdit
          Left = 104
          Top = 24
          Width = 225
          Height = 21
          TabOrder = 1
        end
      end
      object GroupBox10: TGroupBox
        Left = 8
        Top = 24
        Width = 345
        Height = 89
        Caption = 'ROMS'
        TabOrder = 1
        object Label5: TLabel
          Left = 8
          Top = 32
          Width = 75
          Height = 13
          Caption = 'ROMs Directory'
        end
        object rompath: TEdit
          Left = 96
          Top = 24
          Width = 225
          Height = 21
          TabOrder = 0
        end
        object romuse: TCheckBox
          Left = 8
          Top = 56
          Width = 225
          Height = 17
          Caption = 'Use this instead of default "roms"'
          TabOrder = 1
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Video Options'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 0
        Top = 8
        Width = 193
        Height = 81
        Caption = 'Speed specific'
        TabOrder = 0
        object Label1: TLabel
          Left = 16
          Top = 24
          Width = 59
          Height = 13
          Caption = 'Frame Skip: '
        end
        object Label2: TLabel
          Left = 117
          Top = 24
          Width = 42
          Height = 13
          Caption = 'out of 12'
        end
        object frameskip: TEdit
          Left = 80
          Top = 22
          Width = 33
          Height = 21
          Enabled = False
          TabOrder = 0
          Text = '0'
        end
        object frameskipauto: TCheckBox
          Left = 16
          Top = 48
          Width = 97
          Height = 17
          Caption = 'Auto frameskip'
          Checked = True
          State = cbChecked
          TabOrder = 1
          OnClick = frameskipautoClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 96
        Width = 193
        Height = 105
        Caption = 'Visual'
        TabOrder = 1
        object scanlines: TCheckBox
          Left = 8
          Top = 16
          Width = 177
          Height = 17
          Caption = 'scanlines - emulate old scanlines'
          TabOrder = 0
        end
        object switchres: TCheckBox
          Left = 8
          Top = 49
          Width = 177
          Height = 17
          Caption = 'Switch Resolution (to best fit)'
          Checked = True
          State = cbChecked
          TabOrder = 1
        end
        object switchbpp: TCheckBox
          Left = 8
          Top = 64
          Width = 177
          Height = 17
          Caption = 'Switch BPP (switch color depths)'
          Checked = True
          State = cbChecked
          TabOrder = 2
        end
        object hwstretch: TCheckBox
          Left = 8
          Top = 33
          Width = 177
          Height = 17
          Caption = 'hwstretch - hardware vid. stretch'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
        object window: TCheckBox
          Left = 8
          Top = 80
          Width = 113
          Height = 17
          Caption = 'Run in a Window'
          TabOrder = 4
        end
      end
      object GroupBox3: TGroupBox
        Left = 200
        Top = 240
        Width = 161
        Height = 49
        Caption = 'Brightness'
        TabOrder = 2
        object brightness: TLabel
          Left = 138
          Top = 14
          Width = 6
          Height = 13
          Caption = '1'
        end
        object brbar: TTrackBar
          Left = 3
          Top = 12
          Width = 134
          Height = 29
          Max = 20
          Min = 1
          Orientation = trHorizontal
          Frequency = 1
          Position = 10
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          ThumbLength = 15
          TickMarks = tmBoth
          TickStyle = tsNone
          OnChange = brbarChange
        end
      end
      object GroupBox4: TGroupBox
        Left = 200
        Top = 288
        Width = 161
        Height = 49
        Caption = 'Gamma'
        TabOrder = 3
        object gamma: TLabel
          Left = 138
          Top = 15
          Width = 6
          Height = 13
          Caption = '1'
        end
        object gbar: TTrackBar
          Left = 3
          Top = 12
          Width = 134
          Height = 29
          Max = 20
          Min = 1
          Orientation = trHorizontal
          Frequency = 1
          Position = 10
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          ThumbLength = 15
          TickMarks = tmBoth
          TickStyle = tsNone
          OnChange = gbarChange
        end
      end
      object Effects: TRadioGroup
        Left = 200
        Top = 8
        Width = 193
        Height = 81
        Caption = 'Effects'
        Columns = 2
        ItemIndex = 0
        Items.Strings = (
          'none  '
          'scan25'
          'scan50'
          'scan75'
          'rgb3  '
          'rgb4  '
          'rgb6  '
          'rgb16 ')
        TabOrder = 4
      end
      object GroupBox8: TGroupBox
        Left = 0
        Top = 208
        Width = 193
        Height = 129
        Caption = 'Rotation'
        TabOrder = 5
        object norotate: TCheckBox
          Left = 8
          Top = 12
          Width = 97
          Height = 17
          Caption = 'norotate'
          TabOrder = 0
        end
        object ror: TCheckBox
          Left = 8
          Top = 60
          Width = 137
          Height = 17
          Caption = 'rotate screen clockwise'
          TabOrder = 1
        end
        object rol: TCheckBox
          Left = 8
          Top = 76
          Width = 161
          Height = 17
          Caption = 'rotate screen anti-clockwise'
          TabOrder = 2
        end
        object flipx: TCheckBox
          Left = 8
          Top = 108
          Width = 153
          Height = 17
          Caption = 'flip screen left-right'
          TabOrder = 3
        end
        object flipy: TCheckBox
          Left = 8
          Top = 92
          Width = 153
          Height = 17
          Caption = 'flip screen upside-down'
          TabOrder = 4
        end
        object autoror: TCheckBox
          Left = 8
          Top = 28
          Width = 169
          Height = 17
          Hint = 'automatically rotate screen clockwise for  vertical games'
          Caption = 'auto rotate screen clockwise'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 5
        end
        object autorol: TCheckBox
          Left = 8
          Top = 44
          Width = 169
          Height = 17
          Hint = 'automatically rotate screen anti-clockwise for  vertical games'
          Caption = 'auto rot. screen anti-clockwise'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 6
        end
      end
      object RadioGroup1: TRadioGroup
        Left = 200
        Top = 96
        Width = 193
        Height = 105
        Caption = 'ArtWork Options'
        TabOrder = 6
      end
      object artwork: TCheckBox
        Left = 208
        Top = 112
        Width = 177
        Height = 17
        Caption = 'artwork - enable/disable artwork'
        Checked = True
        State = cbChecked
        TabOrder = 7
      end
      object bezels: TCheckBox
        Left = 208
        Top = 128
        Width = 177
        Height = 17
        Caption = 'bezels - display bezels'
        TabOrder = 8
      end
      object overlays: TCheckBox
        Left = 208
        Top = 144
        Width = 177
        Height = 17
        Caption = 'overlays - display overlays'
        TabOrder = 9
      end
      object backdrops: TCheckBox
        Left = 208
        Top = 160
        Width = 177
        Height = 17
        Caption = 'backdrops - display backdrops '
        TabOrder = 10
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'D3D Video Options'
      ImageIndex = 4
      object GroupBox11: TGroupBox
        Left = 0
        Top = 8
        Width = 401
        Height = 329
        Caption = 'Direct 3D'
        TabOrder = 0
        object Label4: TLabel
          Left = 157
          Top = 56
          Width = 124
          Height = 26
          Caption = 'Type of filtering to apply to the image when stretching'
          WordWrap = True
        end
        object d3dtexmanage: TCheckBox
          Left = 8
          Top = 32
          Width = 321
          Height = 17
          Caption = 'd3dtexmanage - more compatible, slower in some hardware'
          Checked = True
          State = cbChecked
          TabOrder = 0
        end
        object direct3d: TCheckBox
          Left = 8
          Top = 16
          Width = 385
          Height = 17
          Caption = 'direct3d - Use Direct3D to display the image, implies hwstretch'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object d3deffect: TRadioGroup
          Left = 8
          Top = 152
          Width = 385
          Height = 161
          Caption = 'd3deffect'
          Columns = 2
          ItemIndex = 0
          Items.Strings = (
            'none - no effect (default)'
            'sharp - no effect, sharper image'
            'scan25 - 25% scanlines'
            'scan50 - 50% scanlines'
            'scan75 - 75% scanlines'
            'scan75v - 75% scanlines (vert.)'
            'rgbmicro - a "monitor mask"'
            'rgbtiny - another one'
            'rgb3 - another one'
            'rgb4 - another one'
            'rgb4v - another one (vertical)'
            'rgb6 - another one'
            'rgb16 - another one'
            'rgbminmask - another one'
            'dotmedmask - another one'
            'rgbmedmask - another one'
            'dotmedbright - another extra bright'
            'rgbmaxbright - another extra bright'
            'aperturegrille - another one'
            'auto - select based on zoom level ')
          TabOrder = 2
        end
        object GroupBox12: TGroupBox
          Left = 192
          Top = 104
          Width = 201
          Height = 41
          Hint = 
            'scanline effect intensity in percentages. 0 is black lines  betw' +
            'een scanlines, 100 is disable effect.'
          Caption = 'Scanline Intensity'
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          object scanlbl: TLabel
            Left = 160
            Top = 16
            Width = 33
            Height = 13
            Hint = 
              'scanline effect intensity in percentages. 0 is black lines  betw' +
              'een scanlines, 100 is disable effect.'
            Caption = '100'
            ParentShowHint = False
            ShowHint = True
          end
          object d3dscanbar: TTrackBar
            Left = 3
            Top = 12
            Width = 150
            Height = 21
            Max = 100
            Orientation = trHorizontal
            Frequency = 1
            Position = 100
            SelEnd = 0
            SelStart = 0
            TabOrder = 0
            ThumbLength = 15
            TickMarks = tmBoth
            TickStyle = tsNone
            OnChange = d3dscanbarChange
          end
        end
      end
      object d3dfilter: TRadioGroup
        Left = 8
        Top = 56
        Width = 145
        Height = 97
        Caption = 'd3dfilter'
        ItemIndex = 1
        Items.Strings = (
          'none'
          'bi-linear (default)'
          'flat bi-cubic'
          'gaussian bicubic'
          'anisotropic (if supported)')
        TabOrder = 1
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Audio / Input'
      ImageIndex = 2
      object GroupBox5: TGroupBox
        Left = 184
        Top = 104
        Width = 177
        Height = 57
        Caption = 'Sample Rate'
        TabOrder = 0
        object SRate: TComboBox
          Left = 40
          Top = 20
          Width = 97
          Height = 21
          ItemHeight = 13
          TabOrder = 0
          Text = '44100'
          OnKeyPress = SRateKeyPress
          Items.Strings = (
            '8000'
            '11000'
            '22000'
            '32000'
            '44100')
        end
      end
      object GroupBox6: TGroupBox
        Left = 8
        Top = 16
        Width = 161
        Height = 185
        Caption = 'Input Device Options'
        TabOrder = 1
        object joystick: TCheckBox
          Left = 16
          Top = 32
          Width = 97
          Height = 17
          Caption = 'Use Joystick'
          TabOrder = 0
        end
        object mouse: TCheckBox
          Left = 16
          Top = 16
          Width = 97
          Height = 17
          Caption = 'Use Mouse'
          TabOrder = 1
        end
        object steadykey: TCheckBox
          Left = 16
          Top = 64
          Width = 97
          Height = 17
          Caption = 'Use Steadykey'
          TabOrder = 2
        end
        object lightgun: TCheckBox
          Left = 16
          Top = 48
          Width = 97
          Height = 17
          Caption = 'Use Lightgun'
          TabOrder = 3
        end
        object ledemul: TCheckBox
          Left = 16
          Top = 80
          Width = 105
          Height = 17
          Caption = 'keyb. LED emul.'
          TabOrder = 4
        end
        object Panel1: TPanel
          Left = 8
          Top = 112
          Width = 145
          Height = 65
          TabOrder = 5
          object wantctrlr: TCheckBox
            Left = 8
            Top = 8
            Width = 97
            Height = 17
            Caption = 'Preconfigure For:'
            TabOrder = 0
          end
          object ctrlredt: TEdit
            Left = 8
            Top = 32
            Width = 129
            Height = 21
            Hint = 'Controller Name (e.g. hotrod)'
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
          end
        end
      end
      object GroupBox7: TGroupBox
        Left = 184
        Top = 16
        Width = 177
        Height = 81
        Caption = 'Volume'
        TabOrder = 2
        object Volume: TLabel
          Left = 64
          Top = 48
          Width = 19
          Height = 13
          Caption = '0dB'
        end
        object volbar: TTrackBar
          Left = 8
          Top = 16
          Width = 150
          Height = 33
          Max = 32
          Orientation = trHorizontal
          Frequency = 1
          Position = 32
          SelEnd = 0
          SelStart = 0
          TabOrder = 0
          ThumbLength = 15
          TickMarks = tmBoth
          TickStyle = tsNone
          OnChange = volbarChange
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Other'
      ImageIndex = 3
      object cheats: TCheckBox
        Left = 8
        Top = 16
        Width = 97
        Height = 17
        Caption = 'Enable Cheats'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object skipgameinfo: TCheckBox
        Left = 8
        Top = 40
        Width = 97
        Height = 17
        Caption = 'skipgameinfo'
        TabOrder = 1
      end
      object skipdisclaimer: TCheckBox
        Left = 8
        Top = 64
        Width = 97
        Height = 17
        Caption = 'skipdisclaimer'
        TabOrder = 2
      end
    end
  end
  object MOKBtn: TBitBtn
    Left = 288
    Top = 376
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 3
    OnClick = MOKBtnClick
  end
  object usethem: TCheckBox
    Left = 16
    Top = 384
    Width = 129
    Height = 17
    Caption = 'Use these settings'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
  end
end
