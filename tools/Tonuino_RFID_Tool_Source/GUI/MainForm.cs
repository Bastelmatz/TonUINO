using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tonuino_RFID_Creator
{
    public partial class MainForm : Form
    {
        public static MainForm Instance { get; set; }

        private static bool checkPorts = false;

        public MainForm()
        {
            InitializeComponent();

            Instance = this;

            initGUI();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            checkPorts = true;
            Task.Run(() => checkPortsThread());
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            checkPorts = false;
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
            pnlModiCardAction.Location = pnlMusicCardAction.Location;

            // set music card mode options
            List<MusicMode> cardModes = MusicMode.AllValidModes();
            comboBox_MusicCardModes.SetItems(cardModes);

            // set modi card options
            List<ModiType> modiTypes = ModiType.AllValidModes();
            comboBox_ModiCardOptions.SetItems(modiTypes);
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
            while (checkPorts)
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
            bool useSingleTrack = false;
            bool isModifierCard = false;
            bool isSleepModi = false;
            if (data is MusicCardData)
            {
                MusicCardData musicData = (MusicCardData)data;
                useStartEndTrack = musicData.Mode.UseStartEndTrack;
                useSingleTrack = musicData.Mode.UseSingleTrack;

                setText(lblFolder, musicData.Folder);
                setText(lblStartPos, musicData.StartPos);
                setText(lblEndPos, musicData.EndPos);
                lblMode.Text = musicData.Mode.Name;
                lblStartPosCaption.Text = useSingleTrack ? "Track:" : "Start Track:";
            }
            if (data is ModiCardData)
            {
                isModifierCard = true;
                ModiCardData modiData = (ModiCardData)data;
                isSleepModi = modiData.ModiType.UseSleepTimeSetting;

                lblMode.Text = modiData.ModiType.Name;
                lblSleepTime.Text = modiData.SleepTime.Minutes + " min";
            }

            lblCardDetected.Text = "Card Data - " + (exists ? data.IsNewCard ? "New" : "Tonuino " + (isModifierCard ? "Modification" : "Music") : "No") + " Card";
            lblRFID.Text = data.RFID + " | Hex: " + data.RFIDHex;

            // Visibility
            radio_ModiCard.Checked = isModifierCard;
            radio_MusicCard.Checked = !isModifierCard; // in case control isn't visible
            pnlCardDetected.Visible = pnlCardAction.Visible = exists;
            updateCardActionVisibility();

            lblFolderCaption.Visible = lblFolder.Visible = !isModifierCard;
            lblEndPosCaption.Visible = lblEndPos.Visible = useStartEndTrack;
            lblStartPosCaption.Visible = lblStartPos.Visible = useStartEndTrack || useSingleTrack;
            lblSleepTimeReadCaption.Visible = lblSleepTime.Visible = isModifierCard && isSleepModi;
        }

        private void updateCardActionVisibility()
        {
            pnlModiCardAction.Visible = pnlCardAction.Visible && radio_ModiCard.Checked;
            pnlMusicCardAction.Visible = pnlCardAction.Visible && radio_MusicCard.Checked;

            updateWriteDataControls();
        }

        private void updateWriteDataControls()
        {
            if (pnlMusicCardAction.Visible)
            {
                MusicMode mode = (MusicMode)comboBox_MusicCardModes.SelectedItem;
                bool useStartEndTrack = mode == null ? false : mode.UseStartEndTrack;
                bool useSingleTrack = mode == null ? false : mode.UseSingleTrack;

                textBoxEndOnSD.Visible = lblEndOnSource.Visible = useStartEndTrack;
                textBoxStartOnSD.Visible = lblStartOnSource.Visible = useStartEndTrack || useSingleTrack;
                lblStartOnSource.Text = useSingleTrack ? "track" : "start track";
            }
            if (pnlModiCardAction.Visible)
            {
                ModiType modiType = (ModiType)comboBox_ModiCardOptions.SelectedItem;
                bool useSleepTime = modiType == null ? false : modiType.UseSleepTimeSetting;

                textBox_SleepTime.Visible = lblSleepTimeCaption.Visible = lblSleepTimeUnit.Visible = useSleepTime;
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

        private ICardData getMusicCardData()
        {
            MusicMode mode = (MusicMode)comboBox_MusicCardModes.SelectedItem;
            byte folder = getByte(textBoxFolderOnSD);
            byte startTrack = getByte(textBoxStartOnSD);
            byte endTrack = getByte(textBoxEndOnSD);

            ICardData musicData = new CardDataRaw()
            {
                Raw_Folder = folder,
                Raw_Mode = mode.Ident.Index,
                Raw_Special = startTrack,
                Raw_Special2 = endTrack
            };
            return musicData;
        }

        private ICardData getModiCardData()
        {
            ModiType modiType = (ModiType)comboBox_ModiCardOptions.SelectedItem;
            byte sleepTime = getByte(textBox_SleepTime);

            ICardData modiData = new CardDataRaw()
            {
                Raw_Folder = 0,
                Raw_Mode = modiType.Ident.Index,
                Raw_Special = sleepTime,
                Raw_Special2 = 0
            };
            return modiData;
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
            ICardData cardData = getMusicCardData();
            SerialComm.Write(cardData);
        }

        private void btnWriteModiCard_Click(object sender, EventArgs e)
        {
            ICardData cardData = getModiCardData();
            SerialComm.Write(cardData);
        }

        private void radio_Card_CheckedChanged(object sender, EventArgs e)
        {
            updateCardActionVisibility();
        }

        private void textBoxSetting_Time_TextChanged(object sender, EventArgs e)
        {
            limitText((TextBox)sender, 0, 60);
        }

        private void textBoxFolderOnSD_TextChanged(object sender, EventArgs e)
        {
            limitText(textBoxFolderOnSD, 99);
        }

        private void textBoxStartOnSD_TextChanged(object sender, EventArgs e)
        {
            limitText(textBoxStartOnSD, 255);
        }

        private void textBoxEndOnSD_TextChanged(object sender, EventArgs e)
        {
            limitText(textBoxEndOnSD, 255);
        }

        private void comboBoxCardModes_SelectedValueChanged(object sender, EventArgs e)
        {
            updateWriteDataControls();
            btnBrowsMusic.Select();
        }

        private void comboBox_ModiCardOptions_SelectedIndexChanged(object sender, EventArgs e)
        {
            updateWriteDataControls();
        }

        #endregion
    }
}
