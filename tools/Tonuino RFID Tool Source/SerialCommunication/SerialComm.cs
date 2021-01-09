using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Tonuino_RFID_Creator
{
    public class SerialComm
    {
        // *****************************
        // Port Handling
        // ***************************** 
        #region Port Handling

        public static List<string> FoundPorts = new List<string>();

        public static SerialPort ConnectedPort = null;

        public static bool DoListening = false;
        public static bool IsListening = false;
        public static Task listeningTask = null;

        public static void CheckComPorts()
        {
            string[] portNames = SerialPort.GetPortNames();

            FoundPorts.Clear();
            foreach (string portName in portNames)
            {
                FoundPorts.Add(portName);
            }
        }

        public static void OpenPort(string name)
        {
            ClosePort();

            SerialPort port = new SerialPort(name);

            port.BaudRate = 115200;
            port.Parity = Parity.None;
            port.StopBits = StopBits.One;
            port.DataBits = 8;
            port.Handshake = Handshake.None;
            port.Encoding = Encoding.UTF8;

            port.Open();
            ConnectedPort = port;

            DoListening = true;
            listenPort();
        }

        public static void ClosePort()
        {
            DoListening = false;
            ConnectedPort?.Close();

            DateTime startTime = DateTime.Now;
            // wait for listening task to finish - continue after 5s anyway
            while (IsListening && DateTime.Now - startTime < TimeSpan.FromSeconds(5))
            {
                Thread.Sleep(100);
            }
        }

        public static void WriteLine(string text)
        {
            ConnectedPort?.WriteLine(text);
        }

        private static void listenPort()
        {
            listeningTask = new Task(listenPortAction);

            listeningTask.Start();
        }

        private static void listenPortAction()
        {
            IsListening = true;
            while (ConnectedPort.IsOpen)
            {
                try
                {
                    string receivedData = ConnectedPort.ReadLine();
                    collectForCardData(receivedData);
                    MainForm.Instance.LogText(receivedData);
                }
                catch (Exception e)
                {
                    if (DoListening) // Don't show error if port is regularly closed
                    {
                        MainForm.Instance.LogText(e.Message);
                    }
                }
            }
            IsListening = false;
        }

        #endregion

        // *****************************
        // Card Data Handling
        // ***************************** 
        #region Card Data Handling

        public static CardData CurrentCardRead { get; set; } = new CardData();
        public static AdminSettings AdminSettingsRead { get; set; } = new AdminSettings();

        private static bool collectCardData = false;
        private static List<string> collectedData = new List<string>();

        private static string KEYRead_TriggerBEGIN { get; } = "Tonuino_Admin_Tool_BEGIN";
        private static string KEYRead_TriggerEND { get; } = "Tonuino_Admin_Tool_END";
        private static string KEYRead_CardData { get; } = "CardData";
        private static string KEYRead_AdminSettings { get; } = "AdminSettings";
        private static char Read_KeyValueSeparator { get; } = ':';

        private static void collectForCardData(string receivedText)
        {
            if (receivedText.Contains(KEYRead_TriggerEND))
            {
                // get section
                string section = "";
                if (collectedData.Count > 0)
                {
                    section = collectedData[0];
                    // remove section part
                    collectedData.RemoveAt(0);
                }

                // evaluate received data
                if (section.Contains(KEYRead_CardData))
                {
                    CurrentCardRead = getCardData(collectedData);
                    MainForm.Instance.UpdateCardData();
                }
                if (section.Contains(KEYRead_AdminSettings))
                {
                    AdminSettingsRead = getAdminSettings(collectedData);
                    MainForm.Instance.UpdateAdminSettings();
                }
                collectCardData = false;
            }
            if (collectCardData)
            {
                collectedData.Add(receivedText);
            }
            if (receivedText.Contains(KEYRead_TriggerBEGIN))
            {
                collectedData.Clear();
                collectCardData = true;
            }
        }

        private static CardData getCardData(List<string> textLines)
        {
            CardData data = new CardData();
            if (textLines.Count == 6)
            {
                // Defined order - has to be in sync with Tonuino sketch!!
                long rfid = getLong(textLines[0]);
                int cookie = getInt(textLines[1]);
                int folder = getInt(textLines[2]);
                if (folder == 0)
                {
                    EModiType modiType = ModiType.FromNumber(getInt(textLines[3]));
                    TimeSpan sleepTime = TimeSpan.FromMinutes(getInt(textLines[4]));
                    data = new ModiCardData(rfid, cookie, modiType, sleepTime);
                }
                else
                {
                    EMusicMode mode = MusicMode.FromNumber(getInt(textLines[3]));
                    int start = getInt(textLines[4]);
                    int end = getInt(textLines[5]);
                    data = new MusicCardData(rfid, cookie, mode, folder, start, end);
                }
            }
            return data;
        }

        private static AdminSettings getAdminSettings(List<string> textLines)
        {
            AdminSettings data = new AdminSettings();
            if (textLines.Count == 5)
            {
                // Defined order - has to be in sync with Tonuino sketch!!
                int minVol = getInt(textLines[0]);
                int maxVol = getInt(textLines[1]);
                int initVol = getInt(textLines[2]);
                TimeSpan standbyTime = TimeSpan.FromMinutes(getInt(textLines[3]));
                EEqualizerType equalizer = EqualizerType.FromNumber(getInt(textLines[4]));
                data = new AdminSettings(minVol, initVol, maxVol, standbyTime, equalizer);
            }
            return data;
        }

        private static int getInt(string text)
        {
            return (int)getLong(text);
        }

        private static long getLong(string text)
        {
            text = text.Replace("\r", "");
            text = text.Replace(" ", "");
            string[] splitText = text.Split(Read_KeyValueSeparator);
            if (splitText.Length > 1)
            {
                long number;
                string sValue = splitText[1];
                if (long.TryParse(sValue, out number))
                {
                    return number;
                }
                if (long.TryParse(sValue, NumberStyles.HexNumber, CultureInfo.InvariantCulture, out number))
                {
                    return number;
                }
            }
            return 0;
        }

        public void Write(CardData cardData)
        {
            string formattedLineText = cardData.ToString();

            WriteLine(formattedLineText);
        }

        private static char SEPARATOR { get; } = ';';

        private static string toString(MusicCardData data)
        {
            // Defined order - has to be in sync with Tonuino sketch - don't change!!
            List<object> items = new List<object>()
            {
                data.RFID,
                data.Folder,
                data.Mode.Index,
                data.StartPos,
                data.EndPos
            };
            return string.Join(SEPARATOR.ToString(), items);
        }

        #endregion

    }
}
