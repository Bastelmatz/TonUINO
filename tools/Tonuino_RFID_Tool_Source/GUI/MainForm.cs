﻿using System;
using System.Collections.Generic;
using System.Drawing;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tonuino_RFID_Tool
{
    public partial class MainForm : Form
    {
        public static MainForm Instance { get; set; }

        private static bool m_checkPorts = false;

        private List<TextBox> m_byteBoxes = new List<TextBox>();
        private List<Label> m_byteLabels = new List<Label>();

        public MainForm()
        {
            InitializeComponent();

            Instance = this;

            try
            {
                initGUI();
            }
            catch (Exception ex)
            {
                showException(ex, "Init GUI");
            }
        }

        private void showException(Exception ex, string caption)
        {
            MessageBox.Show(ex.Message, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            m_checkPorts = true;
            Task.Run(() => checkPortsThread());
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_checkPorts = false;
            SerialComm.ClosePort();
        }

        private void doAction(Action action)
        {
            try
            {
                if (InvokeRequired)
                {
                    this.Invoke(action);
                }
                else
                {
                    action();
                }
            }
            catch (Exception ex)
            {
                // Prevent endless loop on logtext exception
                if (action.Method.Name != new Action(() => logText("")).Method.Name)
                {
                    LogText(ex.Message);
                }
            }
        }

        private void initGUI()
        {
            pnlModiCardAction.Location = pnlRawDataAction.Location = pnlMusicCardAction.Location;
            lblReadModiValueCaption.Top = lblReadModiValue.Top = lblFolder.Top;

            // set music card mode options
            List<MusicMode> cardModes = MusicMode.AllValidModes();
            comboBox_MusicCardModes.SetItems(cardModes);

            // set modi card options
            List<ModiType> modiTypes = ModiType.AllValidModes();
            comboBox_ModiCardOptions.SetItems(modiTypes);

            // set modi card bool value options
            List<ModiBoolValue> modiBoolValues = ModiBoolValue.AllValidValues();
            comboBox_ModiBehaviour.SetItems(modiBoolValues);

            m_byteBoxes = new List<TextBox>()
            {
                boxByte01,
                boxByte02,
                boxByte03,
                boxByte04,
                boxByte05,
                boxByte06,
                boxByte07,
                boxByte08,
                boxByte09,
                boxByte10,
                boxByte11,
                boxByte12,
                boxByte13,
                boxByte14,
                boxByte15
            };

            m_byteLabels = new List<Label>()
            {
                lblByte01,
                lblByte02,
                lblByte03,
                lblByte04,
                lblByte05,
                lblByte06,
                lblByte07,
                lblByte08,
                lblByte09,
                lblByte10,
                lblByte11,
                lblByte12,
                lblByte13,
                lblByte14,
                lblByte15
            };

            foreach (Label byteLbl in m_byteLabels)
            {
                byteLbl.BackColor = Color.DimGray;
                byteLbl.ForeColor = Color.White;
            }
        }

        // *****************************
        // Com Port Handling
        // ***************************** 
        #region Com Port Handling

        private void updatePortsList()
        {
            List<string> ports = SerialComm.FoundPorts;
            bool anyListedPortsNotFound = false;
            foreach (string listedPort in comboBox_Ports.Items)
            {
                if (!ports.Contains(listedPort))
                {
                    anyListedPortsNotFound = true;
                    break;
                }
            }
            // Update collection only on change
            if (comboBox_Ports.Items.Count == 0 || anyListedPortsNotFound)
            {
                comboBox_Ports.SetItems(ports);
                UpdateTonuinoData();
            }
        }

        private void checkPortsThread()
        {
            while (m_checkPorts)
            {
                SerialComm.CheckComPorts();
                doAction(() => updatePortsList());
                if (SerialComm.ConnectedPort == null || !SerialComm.ConnectedPort.IsOpen)
                {
                    doAction(() => connectFirstComPort());
                }
                Thread.Sleep(1000);
            }
        }

        private void connectFirstComPort()
        {
            connectComPort("", true);
        }

        private async void connectComPort(string portName, bool useFirstPort)
        {
            btnConnectPort.Enabled = false;
            try
            {
                string validPortName = SerialComm.FoundPorts.Contains(portName) ? portName : "";
                if (useFirstPort && SerialComm.FoundPorts.Count > 0)
                {
                    validPortName = SerialComm.FoundPorts[0];
                }

                lblConnectedPort.Text = "No Port connected";
                if (!string.IsNullOrWhiteSpace(validPortName))
                {
                    logTextBox.Text = "";
                    await Task.Run(() => SerialComm.OpenPort(validPortName));
                    lblConnectedPort.Text = "Connected with port: " + validPortName;
                }
            }
            catch (Exception ex)
            {
                logTextBox.Text = ex.Message;
            }

            UpdateTonuinoData();

            btnConnectPort.Enabled = true;
        }

        #endregion

        // *****************************
        // GUI Update
        // ***************************** 
        #region GUI Update
        
        public void UpdateTonuinoData()
        {
            try
            {
                UpdateCardData();
            }
            catch (Exception ex)
            {
                LogText("Error updating data: " + ex.Message);
            }
        }

        public void UpdateCardData()
        {
            doAction(() => updateCardData());
        }

        private void updateCardData()
        {
            CardData data = SerialComm.CurrentCardRead;
            bool exists = data.Exists && SerialComm.IsListening;

            // Text
            bool useStartEndTrack = false;
            bool useSingleTrio = false;
            bool useEndFolder = false;
            bool useRecentFolder = false;
            bool useRecentTrack = false;
            bool isMusicCard = false;
            bool isModifierCard = false;
            bool hasModiValue = false;
            if (data is MusicCardData)
            {
                isMusicCard = true;
                MusicCardData musicData = (MusicCardData)data;
                MusicMode mode = musicData.Mode;
                useStartEndTrack = mode.UseStartEndTrack;
                useSingleTrio = mode.UseDefinedSingleTrio;
                useEndFolder = mode.UseEndFolder;
                bool useCompareFolder = mode.UseCompareFolder;
                useRecentFolder = mode.UseRecentFolder;
                useRecentTrack = mode.UseRecentTrack;

                setText(lblFolder, musicData.StartFolder);
                setText(lblStartPos, musicData.StartPos);
                setText(lblEndPos, musicData.EndPos);
                setText(lblEndFolder, musicData.EndFolder);
                setText(lblRecentFolder, musicData.RecentFolder);
                setText(lblRecentTrack, musicData.RecentTrack);
                lblMode.Text = mode.Name;
                lblStartPosCaption.Text = (useSingleTrio ? "1." : "Start ") + "Track:";
                lblEndPosCaption.Text = (useSingleTrio ? "2." : "End ") + "Track:";
                lblRecentTrackCaption.Text = (useSingleTrio ? "3." : "Recent ") + "Track:";
                lblFolderCaption.Text = (useEndFolder ? "Start " : "") + "Folder:";
                lblEndFolderCaption.Text = (useCompareFolder ? "Compare" : "End") + " Folder:";

                if (musicData.IsAdvertisement_Start)
                {
                    lblFolder.Text += " (Advertisement)";
                }
                if (musicData.IsAdvertisement_End)
                {
                    lblEndFolder.Text += " (Advertisement)";
                }
            }
            if (data is ModiCardData)
            {
                isModifierCard = true;
                ModiCardData modiData = (ModiCardData)data;
                ModiType modiType = modiData.ModiType;
                hasModiValue = modiType.RequiresValue;

                lblMode.Text = modiType.Name;
                lblReadModiValue.Text = modiData.Value.ToString();
                if (modiType.IsMinutesValue)
                {
                    lblReadModiValue.Text += " min";
                }
                if (modiType.IsBool)
                {
                    lblReadModiValue.Text =  ModiBoolValue.FullNameFromNumber((byte)modiData.Value);
                }
            }

            string cardPrefix = isModifierCard ? "Modification" : "Music";
            lblCardDetected.Text = (exists ? data.IsNewCard ? "New" : "Tonuino " + cardPrefix : "No") + " Card";
            lblRFID.Text = data.RFID.ToString();
            lblHex.Text = data.RFIDHex;

            // Visibility
            if (!data.IsNewCard)
            {
                // legacy modifier not implemented in GUI
                radio_ModiCard.Checked = isModifierCard;
                radio_MusicCard.Checked = !isModifierCard; // in case control isn't visible
            }
            pnlCardDetected.Visible = pnlCardAction.Visible = true; // exists;
            updateCardActionVisibility();

            bool isDefinedCard = isMusicCard || isModifierCard;
            lblModeCaption.Visible = lblMode.Visible = isDefinedCard;
            lblFolderCaption.Visible = lblFolder.Visible = isMusicCard;
            lblEndPosCaption.Visible = lblEndPos.Visible = isDefinedCard && useStartEndTrack;
            lblStartPosCaption.Visible = lblStartPos.Visible = isDefinedCard && useStartEndTrack;
            lblEndFolderCaption.Visible = lblEndFolder.Visible = isDefinedCard && useEndFolder;
            lblReadModiValueCaption.Visible = lblReadModiValue.Visible = isModifierCard && hasModiValue;
            lblRecentTrackCaption.Visible = lblRecentTrack.Visible = isMusicCard && useRecentTrack;
            lblRecentFolderCaption.Visible = lblRecentFolder.Visible = isMusicCard && useRecentFolder;
        }

        private void updateCardActionVisibility()
        {
            pnlModiCardAction.Visible = pnlCardAction.Visible && radio_ModiCard.Checked;
            pnlMusicCardAction.Visible = pnlCardAction.Visible && radio_MusicCard.Checked;
            pnlRawDataAction.Visible = pnlCardAction.Visible && radio_Raw.Checked;

            updateWriteDataControls();
        }

        private void updateWriteDataControls()
        {
            if (pnlMusicCardAction.Visible)
            {
                MusicMode mode = (MusicMode)comboBox_MusicCardModes.SelectedItem;
                bool useStartEndTrack = mode == null ? false : mode.UseStartEndTrack;
                bool useSingleTrio = mode == null ? false : mode.UseDefinedSingleTrio;
                bool useEndFolder = mode == null ? false : mode.UseEndFolder;
                bool useCompareFolder = mode == null ? false : mode.UseCompareFolder;

                textBoxEndTrack.Visible = lblEndOnSource.Visible = useStartEndTrack;
                textBoxStartTrack.Visible = lblStartOnSource.Visible = useStartEndTrack;
                textBoxThirdTrack.Visible = lblThirdTrack.Visible = useSingleTrio;
                lblStartOnSource.Text = (useSingleTrio ? "1. " : "start ") + "track";
                lblEndOnSource.Text = (useSingleTrio ? "2. " : "end ") + "track";
                textBoxEndFolder.Visible = lblWriteEndFolder.Visible = useEndFolder;
                lblWriteStartFolder.Text = (useEndFolder ? "start " : "") + "folder";
                lblWriteEndFolder.Text = (useCompareFolder ? "compare" : "end") + " folder";

                MusicCardDataRaw musicCardData = getMusicCardData();
                if (musicCardData.IsAdvertisement_Start)
                {
                    lblWriteStartFolder.Text += " - Advertisement";
                }
                if (musicCardData.IsAdvertisement_End)
                {
                    lblWriteEndFolder.Text += " - Advertisement";
                }
            }
            if (pnlModiCardAction.Visible)
            {
                ModiType modiType = (ModiType)comboBox_ModiCardOptions.SelectedItem;
                bool requiresValue = modiType == null ? false : modiType.RequiresValue;
                bool isMinutes = modiType == null ? false : modiType.IsMinutesValue;
                bool isBool = modiType == null ? false : modiType.IsBool;

                textBox_ModiValue.Visible = lblModiValue.Visible = requiresValue && !isBool;
                lblMinutes.Visible = isMinutes;

                pnlModeBehaviour.Visible = lblModeBehaviour.Visible = isBool;
            }
            if (pnlRawDataAction.Visible)
            {
                for (int i = 0; i < m_byteBoxes.Count; i++)
                {
                    if (i < RawData.ListBytes.Count)
                    {
                        byte singleByte = RawData.ListBytes[i];
                        m_byteBoxes[i].Text = singleByte.ToString();
                    }
                }
            }
        }

        private void setText(Control label, int nText)
        {
            label.Text = nText.ToString();
        }

        public void LogText(string text)
        {
            doAction(() => logText(text));
        }

        private void logText(string text)
        {
            if (!logTextBox.Text.EndsWith("\n"))
            {
                logTextBox.Text += Environment.NewLine;
            }
            logTextBox.Text += text;

            // scroll to latest text
            logTextBox.SelectionStart = logTextBox.Text.Length;
            logTextBox.ScrollToCaret();
        }

        private void limitText(TextBox textBox, int maximum)
        {
            limitText(textBox, 1, maximum);
        }

        private void limitText(TextBox textBox, int minimum, int maximum)
        {
            int nText;
            string currentText = textBox.Text;
            if (int.TryParse(currentText, out nText))
            {
                nText = Math.Min(Math.Max(nText, minimum), maximum);
                string formattedText = nText.ToString();
                if (currentText != formattedText)
                {
                    textBox.Text = formattedText;
                }
            }
            else
            {
                textBox.Text = "1";
            }
        }

        #endregion

        // *****************************
        // Data Handling
        // ***************************** 
        #region Data Handling

        private byte getByte(TextBox textBox)
        {
            string text = textBox.Text;
            byte parsedByte = 0;
            if (textBox.Visible && byte.TryParse(text, out parsedByte))
            {
                return parsedByte;
            }
            return 0;
        }

        private ushort getShort(TextBox textBox)
        {
            string text = textBox.Text;
            ushort parsedInt = 0;
            if (textBox.Visible && ushort.TryParse(text, out parsedInt))
            {
                return parsedInt;
            }
            return 0;
        }

        private MusicCardDataRaw getMusicCardData()
        {
            MusicMode mode = (MusicMode)comboBox_MusicCardModes.SelectedItem;
            byte startFolder = getByte(textBoxStartFolder);
            ushort startTrack = getShort(textBoxStartTrack);
            ushort endTrack = getShort(textBoxEndTrack);
            byte endFolder = getByte(textBoxEndFolder);
            ushort thirdTrack = getByte(textBoxThirdTrack);

            MusicCardDataRaw musicData = new MusicCardDataRaw()
            {
                Raw_StartFolder = startFolder,
                Raw_Mode = mode.Ident.Index,
                Raw_Special = startTrack,
                Raw_Special2 = endTrack,
                Raw_EndFolder = endFolder,
                Raw_RecentTrack = thirdTrack,
            };
            return musicData;
        }

        private IModiCardData getModiCardData()
        {
            ModiType modiType = (ModiType)comboBox_ModiCardOptions.SelectedItem;
            ModiBoolValue modiBoolValue = (ModiBoolValue)comboBox_ModiBehaviour.SelectedItem;
            ushort modiValue = textBox_ModiValue.Visible ? getShort(textBox_ModiValue) : modiBoolValue.Ident.Index;

            IModiCardData modiData = new ModiCardDataRaw()
            {
                Raw_Mode = modiType.Ident.Index,
                Raw_Value = modiValue,
            };
            return modiData;
        }

        private List<byte> getRawData()
        {
            List<byte> listBytes = new List<byte>();
            foreach (TextBox byteBox in m_byteBoxes)
            {
                listBytes.Add(getByte(byteBox));
            }
            return listBytes;
        }

        private void updateByteInList(TextBox textBox)
        {
            for (int i = 0; i < m_byteBoxes.Count; i++)
            {
                if (i < RawData.ListBytes.Count && m_byteBoxes[i] == textBox)
                {
                    RawData.SetByte(i, getByte(textBox));
                }
            }
        }

        #endregion

        // *****************************
        // GUI Action
        // ***************************** 
        #region GUI Action

        private void btnConnect_Click(object sender, EventArgs e)
        {
            object selItem = comboBox_Ports.SelectedItem;
            if (selItem != null)
            {
                connectComPort(selItem.ToString(), false);
            }
            else
            {
                connectFirstComPort();
            }
        }

        private void btnWriteMusicCard_Click(object sender, EventArgs e)
        {
            IMusicCardData cardData = getMusicCardData();
            SerialComm.Write(cardData);
        }

        private void btnWriteModiCard_Click(object sender, EventArgs e)
        {
            IModiCardData cardData = getModiCardData();
            SerialComm.Write(cardData);
        }

        private void btnWriteRawCard_Click(object sender, EventArgs e)
        {
            List<byte> listBytes = getRawData();
            SerialComm.Write(listBytes);
        }

        private void btnResetCard_Click(object sender, EventArgs e)
        {
            SerialComm.ResetCard();
        }

        private void radio_Card_CheckedChanged(object sender, EventArgs e)
        {
            updateCardActionVisibility();
        }

        private void textBoxSetting_ModiValue_TextChanged(object sender, EventArgs e)
        {
            limitText((TextBox)sender, 0, 999);
        }

        private void textBoxStartFolder_TextChanged(object sender, EventArgs e)
        {
            limitText(textBoxStartFolder, CardData.MAX_FOLDER);
            updateWriteDataControls();
        }

        private void textBoxEndFolder_TextChanged(object sender, EventArgs e)
        {
            int min = 0;
            MusicMode mode = (MusicMode)comboBox_MusicCardModes.SelectedItem;
            if (mode != null && mode.UseEndFolderBehindStartFolder)
            {
                int.TryParse(textBoxStartFolder.Text, out min);
            }
            limitText(textBoxEndFolder, Math.Max(min, 1), CardData.MAX_FOLDER);
            updateWriteDataControls();
        }

        private void limitTrack(TextBox trackBox, TextBox folderBox)
        {
            int folder = 0;
            int.TryParse(folderBox.Text, out folder);
            limitText(trackBox, CardData.GetMaxTrack(folder));
        }

        private void textBoxStartOnSD_TextChanged(object sender, EventArgs e)
        {
            limitTrack(textBoxStartTrack, textBoxStartFolder);
        }

        private void textBoxEndOnSD_TextChanged(object sender, EventArgs e)
        {
            limitTrack(textBoxEndTrack, textBoxEndFolder);
        }

        private void boxByte_TextChanged(object sender, EventArgs e)
        {
            if (sender is TextBox)
            {
                TextBox textBox = (TextBox)sender;
                limitText(textBox, 0, 255);
                updateByteInList(textBox);
            }
        }

        private void comboBoxCardModes_SelectedValueChanged(object sender, EventArgs e)
        {
            updateWriteDataControls();
        }

        private void comboBox_ModiCardOptions_SelectedIndexChanged(object sender, EventArgs e)
        {
            updateWriteDataControls();
        }
        #endregion
    }
}
