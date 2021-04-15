namespace Tonuino_RFID_Tool
{
    partial class MainForm
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.lblConnectedPort = new System.Windows.Forms.Label();
            this.btnConnectPort = new System.Windows.Forms.Button();
            this.logTextBox = new System.Windows.Forms.RichTextBox();
            this.lblCardDetected = new System.Windows.Forms.Label();
            this.lblRFIDCaption = new System.Windows.Forms.Label();
            this.lblRFID = new System.Windows.Forms.Label();
            this.lblModeCaption = new System.Windows.Forms.Label();
            this.lblMode = new System.Windows.Forms.Label();
            this.lblFolderCaption = new System.Windows.Forms.Label();
            this.lblFolder = new System.Windows.Forms.Label();
            this.lblStartPosCaption = new System.Windows.Forms.Label();
            this.lblStartPos = new System.Windows.Forms.Label();
            this.lblEndPosCaption = new System.Windows.Forms.Label();
            this.lblEndPos = new System.Windows.Forms.Label();
            this.lblWriteStartFolder = new System.Windows.Forms.Label();
            this.lblStartOnSource = new System.Windows.Forms.Label();
            this.textBoxStartFolder = new System.Windows.Forms.TextBox();
            this.textBoxStartOnSD = new System.Windows.Forms.TextBox();
            this.textBoxEndOnSD = new System.Windows.Forms.TextBox();
            this.lblEndOnSource = new System.Windows.Forms.Label();
            this.btnWriteMusicCard = new System.Windows.Forms.Button();
            this.pnlModes = new System.Windows.Forms.Panel();
            this.comboBox_MusicCardModes = new Tonuino_RFID_Tool.ExtendedComboBox();
            this.pnlCardDetected = new System.Windows.Forms.Panel();
            this.lblRecentTrackCaption = new System.Windows.Forms.Label();
            this.lblRecentTrack = new System.Windows.Forms.Label();
            this.lblRecentFolderCaption = new System.Windows.Forms.Label();
            this.lblRecentFolder = new System.Windows.Forms.Label();
            this.lblEndFolderCaption = new System.Windows.Forms.Label();
            this.lblEndFolder = new System.Windows.Forms.Label();
            this.lblHex = new System.Windows.Forms.Label();
            this.lblHexCaption = new System.Windows.Forms.Label();
            this.lblReadModiValueCaption = new System.Windows.Forms.Label();
            this.lblReadModiValue = new System.Windows.Forms.Label();
            this.pnlModiCardAction = new System.Windows.Forms.Panel();
            this.pnlModeBehaviour = new System.Windows.Forms.Panel();
            this.comboBox_ModiBehaviour = new Tonuino_RFID_Tool.ExtendedComboBox();
            this.lblModeBehaviour = new System.Windows.Forms.Label();
            this.lblMinutes = new System.Windows.Forms.Label();
            this.lblModiValue = new System.Windows.Forms.Label();
            this.textBox_ModiValue = new System.Windows.Forms.TextBox();
            this.pnlModeCardOptions = new System.Windows.Forms.Panel();
            this.comboBox_ModiCardOptions = new Tonuino_RFID_Tool.ExtendedComboBox();
            this.btnWriteModiCard = new System.Windows.Forms.Button();
            this.pnlMusicCardAction = new System.Windows.Forms.Panel();
            this.lblWriteEndFolder = new System.Windows.Forms.Label();
            this.textBoxEndFolder = new System.Windows.Forms.TextBox();
            this.radio_MusicCard = new System.Windows.Forms.RadioButton();
            this.radio_ModiCard = new System.Windows.Forms.RadioButton();
            this.pnlCardAction = new System.Windows.Forms.Panel();
            this.radio_Raw = new System.Windows.Forms.RadioButton();
            this.pnlSeparator = new System.Windows.Forms.Panel();
            this.pnlPorts = new System.Windows.Forms.Panel();
            this.comboBox_Ports = new Tonuino_RFID_Tool.ExtendedComboBox();
            this.lblPorts = new System.Windows.Forms.Label();
            this.btnResetCard = new System.Windows.Forms.Button();
            this.lblRead = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.pnlRawDataAction = new System.Windows.Forms.Panel();
            this.lblByte15 = new System.Windows.Forms.Label();
            this.boxByte15 = new System.Windows.Forms.TextBox();
            this.lblByte14 = new System.Windows.Forms.Label();
            this.boxByte14 = new System.Windows.Forms.TextBox();
            this.lblByte13 = new System.Windows.Forms.Label();
            this.boxByte13 = new System.Windows.Forms.TextBox();
            this.lblByte12 = new System.Windows.Forms.Label();
            this.boxByte12 = new System.Windows.Forms.TextBox();
            this.lblByte11 = new System.Windows.Forms.Label();
            this.boxByte11 = new System.Windows.Forms.TextBox();
            this.lblByte10 = new System.Windows.Forms.Label();
            this.boxByte10 = new System.Windows.Forms.TextBox();
            this.lblByte09 = new System.Windows.Forms.Label();
            this.boxByte09 = new System.Windows.Forms.TextBox();
            this.lblByte08 = new System.Windows.Forms.Label();
            this.boxByte08 = new System.Windows.Forms.TextBox();
            this.lblByte07 = new System.Windows.Forms.Label();
            this.boxByte07 = new System.Windows.Forms.TextBox();
            this.lblByte06 = new System.Windows.Forms.Label();
            this.boxByte06 = new System.Windows.Forms.TextBox();
            this.lblByte05 = new System.Windows.Forms.Label();
            this.boxByte05 = new System.Windows.Forms.TextBox();
            this.lblByte04 = new System.Windows.Forms.Label();
            this.boxByte04 = new System.Windows.Forms.TextBox();
            this.lblByte03 = new System.Windows.Forms.Label();
            this.boxByte03 = new System.Windows.Forms.TextBox();
            this.lblByte02 = new System.Windows.Forms.Label();
            this.boxByte02 = new System.Windows.Forms.TextBox();
            this.lblByte01 = new System.Windows.Forms.Label();
            this.boxByte01 = new System.Windows.Forms.TextBox();
            this.btnWriteRawCard = new System.Windows.Forms.Button();
            this.pnlModes.SuspendLayout();
            this.pnlCardDetected.SuspendLayout();
            this.pnlModiCardAction.SuspendLayout();
            this.pnlModeBehaviour.SuspendLayout();
            this.pnlModeCardOptions.SuspendLayout();
            this.pnlMusicCardAction.SuspendLayout();
            this.pnlCardAction.SuspendLayout();
            this.pnlPorts.SuspendLayout();
            this.pnlRawDataAction.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblConnectedPort
            // 
            this.lblConnectedPort.AutoSize = true;
            this.lblConnectedPort.Location = new System.Drawing.Point(241, 23);
            this.lblConnectedPort.Name = "lblConnectedPort";
            this.lblConnectedPort.Size = new System.Drawing.Size(10, 13);
            this.lblConnectedPort.TabIndex = 1;
            this.lblConnectedPort.Text = " ";
            // 
            // btnConnectPort
            // 
            this.btnConnectPort.Location = new System.Drawing.Point(165, 18);
            this.btnConnectPort.Name = "btnConnectPort";
            this.btnConnectPort.Size = new System.Drawing.Size(70, 23);
            this.btnConnectPort.TabIndex = 3;
            this.btnConnectPort.Text = "Connect";
            this.btnConnectPort.UseVisualStyleBackColor = true;
            this.btnConnectPort.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // logTextBox
            // 
            this.logTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.logTextBox.Font = new System.Drawing.Font("Consolas", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.logTextBox.Location = new System.Drawing.Point(432, 2);
            this.logTextBox.Name = "logTextBox";
            this.logTextBox.ReadOnly = true;
            this.logTextBox.Size = new System.Drawing.Size(349, 403);
            this.logTextBox.TabIndex = 4;
            this.logTextBox.Text = "";
            // 
            // lblCardDetected
            // 
            this.lblCardDetected.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCardDetected.Location = new System.Drawing.Point(7, 83);
            this.lblCardDetected.Name = "lblCardDetected";
            this.lblCardDetected.Size = new System.Drawing.Size(203, 22);
            this.lblCardDetected.TabIndex = 5;
            this.lblCardDetected.Text = "Current Card";
            this.lblCardDetected.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblRFIDCaption
            // 
            this.lblRFIDCaption.Location = new System.Drawing.Point(22, 5);
            this.lblRFIDCaption.Name = "lblRFIDCaption";
            this.lblRFIDCaption.Size = new System.Drawing.Size(45, 13);
            this.lblRFIDCaption.TabIndex = 6;
            this.lblRFIDCaption.Text = "RFID:";
            this.lblRFIDCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblRFID
            // 
            this.lblRFID.AutoSize = true;
            this.lblRFID.Location = new System.Drawing.Point(66, 5);
            this.lblRFID.Name = "lblRFID";
            this.lblRFID.Size = new System.Drawing.Size(35, 13);
            this.lblRFID.TabIndex = 7;
            this.lblRFID.Text = "label4";
            // 
            // lblModeCaption
            // 
            this.lblModeCaption.Location = new System.Drawing.Point(4, 60);
            this.lblModeCaption.Name = "lblModeCaption";
            this.lblModeCaption.Size = new System.Drawing.Size(64, 13);
            this.lblModeCaption.TabIndex = 8;
            this.lblModeCaption.Text = "Mode:";
            this.lblModeCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblMode
            // 
            this.lblMode.AutoSize = true;
            this.lblMode.Location = new System.Drawing.Point(66, 60);
            this.lblMode.Name = "lblMode";
            this.lblMode.Size = new System.Drawing.Size(35, 13);
            this.lblMode.TabIndex = 9;
            this.lblMode.Text = "label6";
            // 
            // lblFolderCaption
            // 
            this.lblFolderCaption.Location = new System.Drawing.Point(3, 96);
            this.lblFolderCaption.Name = "lblFolderCaption";
            this.lblFolderCaption.Size = new System.Drawing.Size(80, 13);
            this.lblFolderCaption.TabIndex = 10;
            this.lblFolderCaption.Text = "Folder:";
            this.lblFolderCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblFolder
            // 
            this.lblFolder.AutoSize = true;
            this.lblFolder.Location = new System.Drawing.Point(90, 96);
            this.lblFolder.Name = "lblFolder";
            this.lblFolder.Size = new System.Drawing.Size(35, 13);
            this.lblFolder.TabIndex = 11;
            this.lblFolder.Text = "label8";
            // 
            // lblStartPosCaption
            // 
            this.lblStartPosCaption.Location = new System.Drawing.Point(3, 121);
            this.lblStartPosCaption.Name = "lblStartPosCaption";
            this.lblStartPosCaption.Size = new System.Drawing.Size(80, 13);
            this.lblStartPosCaption.TabIndex = 12;
            this.lblStartPosCaption.Text = "Start Track:";
            this.lblStartPosCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblStartPos
            // 
            this.lblStartPos.AutoSize = true;
            this.lblStartPos.Location = new System.Drawing.Point(90, 121);
            this.lblStartPos.Name = "lblStartPos";
            this.lblStartPos.Size = new System.Drawing.Size(41, 13);
            this.lblStartPos.TabIndex = 13;
            this.lblStartPos.Text = "label10";
            // 
            // lblEndPosCaption
            // 
            this.lblEndPosCaption.Location = new System.Drawing.Point(3, 147);
            this.lblEndPosCaption.Name = "lblEndPosCaption";
            this.lblEndPosCaption.Size = new System.Drawing.Size(80, 13);
            this.lblEndPosCaption.TabIndex = 14;
            this.lblEndPosCaption.Text = "End Track:";
            this.lblEndPosCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblEndPos
            // 
            this.lblEndPos.AutoSize = true;
            this.lblEndPos.Location = new System.Drawing.Point(90, 147);
            this.lblEndPos.Name = "lblEndPos";
            this.lblEndPos.Size = new System.Drawing.Size(41, 13);
            this.lblEndPos.TabIndex = 15;
            this.lblEndPos.Text = "label12";
            // 
            // lblWriteStartFolder
            // 
            this.lblWriteStartFolder.AutoSize = true;
            this.lblWriteStartFolder.Location = new System.Drawing.Point(68, 66);
            this.lblWriteStartFolder.Name = "lblWriteStartFolder";
            this.lblWriteStartFolder.Size = new System.Drawing.Size(33, 13);
            this.lblWriteStartFolder.TabIndex = 17;
            this.lblWriteStartFolder.Text = "folder";
            // 
            // lblStartOnSource
            // 
            this.lblStartOnSource.AutoSize = true;
            this.lblStartOnSource.Location = new System.Drawing.Point(68, 91);
            this.lblStartOnSource.Name = "lblStartOnSource";
            this.lblStartOnSource.Size = new System.Drawing.Size(54, 13);
            this.lblStartOnSource.TabIndex = 18;
            this.lblStartOnSource.Text = "start track";
            // 
            // textBoxStartFolder
            // 
            this.textBoxStartFolder.Location = new System.Drawing.Point(9, 63);
            this.textBoxStartFolder.MaxLength = 3;
            this.textBoxStartFolder.Name = "textBoxStartFolder";
            this.textBoxStartFolder.Size = new System.Drawing.Size(53, 20);
            this.textBoxStartFolder.TabIndex = 19;
            this.textBoxStartFolder.TextChanged += new System.EventHandler(this.textBoxStartFolder_TextChanged);
            // 
            // textBoxStartOnSD
            // 
            this.textBoxStartOnSD.Location = new System.Drawing.Point(9, 88);
            this.textBoxStartOnSD.MaxLength = 4;
            this.textBoxStartOnSD.Name = "textBoxStartOnSD";
            this.textBoxStartOnSD.Size = new System.Drawing.Size(53, 20);
            this.textBoxStartOnSD.TabIndex = 20;
            this.textBoxStartOnSD.TextChanged += new System.EventHandler(this.textBoxStartOnSD_TextChanged);
            // 
            // textBoxEndOnSD
            // 
            this.textBoxEndOnSD.Location = new System.Drawing.Point(9, 113);
            this.textBoxEndOnSD.MaxLength = 4;
            this.textBoxEndOnSD.Name = "textBoxEndOnSD";
            this.textBoxEndOnSD.Size = new System.Drawing.Size(53, 20);
            this.textBoxEndOnSD.TabIndex = 22;
            this.textBoxEndOnSD.TextChanged += new System.EventHandler(this.textBoxEndOnSD_TextChanged);
            // 
            // lblEndOnSource
            // 
            this.lblEndOnSource.AutoSize = true;
            this.lblEndOnSource.Location = new System.Drawing.Point(68, 116);
            this.lblEndOnSource.Name = "lblEndOnSource";
            this.lblEndOnSource.Size = new System.Drawing.Size(52, 13);
            this.lblEndOnSource.TabIndex = 21;
            this.lblEndOnSource.Text = "end track";
            // 
            // btnWriteMusicCard
            // 
            this.btnWriteMusicCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.btnWriteMusicCard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnWriteMusicCard.Location = new System.Drawing.Point(9, 177);
            this.btnWriteMusicCard.Name = "btnWriteMusicCard";
            this.btnWriteMusicCard.Size = new System.Drawing.Size(175, 23);
            this.btnWriteMusicCard.TabIndex = 24;
            this.btnWriteMusicCard.Text = "Write Music Card";
            this.btnWriteMusicCard.UseVisualStyleBackColor = false;
            this.btnWriteMusicCard.Click += new System.EventHandler(this.btnWriteMusicCard_Click);
            // 
            // pnlModes
            // 
            this.pnlModes.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlModes.Controls.Add(this.comboBox_MusicCardModes);
            this.pnlModes.Location = new System.Drawing.Point(9, 23);
            this.pnlModes.Name = "pnlModes";
            this.pnlModes.Size = new System.Drawing.Size(175, 23);
            this.pnlModes.TabIndex = 27;
            // 
            // comboBox_MusicCardModes
            // 
            this.comboBox_MusicCardModes.BackColor = System.Drawing.SystemColors.Window;
            this.comboBox_MusicCardModes.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox_MusicCardModes.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_MusicCardModes.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.comboBox_MusicCardModes.FormattingEnabled = true;
            this.comboBox_MusicCardModes.Location = new System.Drawing.Point(0, 0);
            this.comboBox_MusicCardModes.Name = "comboBox_MusicCardModes";
            this.comboBox_MusicCardModes.Size = new System.Drawing.Size(173, 21);
            this.comboBox_MusicCardModes.TabIndex = 16;
            this.comboBox_MusicCardModes.SelectedValueChanged += new System.EventHandler(this.comboBoxCardModes_SelectedValueChanged);
            // 
            // pnlCardDetected
            // 
            this.pnlCardDetected.Controls.Add(this.lblRecentTrackCaption);
            this.pnlCardDetected.Controls.Add(this.lblRecentTrack);
            this.pnlCardDetected.Controls.Add(this.lblRecentFolderCaption);
            this.pnlCardDetected.Controls.Add(this.lblRecentFolder);
            this.pnlCardDetected.Controls.Add(this.lblEndFolderCaption);
            this.pnlCardDetected.Controls.Add(this.lblEndFolder);
            this.pnlCardDetected.Controls.Add(this.lblHex);
            this.pnlCardDetected.Controls.Add(this.lblHexCaption);
            this.pnlCardDetected.Controls.Add(this.lblReadModiValueCaption);
            this.pnlCardDetected.Controls.Add(this.lblReadModiValue);
            this.pnlCardDetected.Controls.Add(this.lblRFIDCaption);
            this.pnlCardDetected.Controls.Add(this.lblRFID);
            this.pnlCardDetected.Controls.Add(this.lblModeCaption);
            this.pnlCardDetected.Controls.Add(this.lblMode);
            this.pnlCardDetected.Controls.Add(this.lblFolderCaption);
            this.pnlCardDetected.Controls.Add(this.lblFolder);
            this.pnlCardDetected.Controls.Add(this.lblStartPosCaption);
            this.pnlCardDetected.Controls.Add(this.lblStartPos);
            this.pnlCardDetected.Controls.Add(this.lblEndPosCaption);
            this.pnlCardDetected.Controls.Add(this.lblEndPos);
            this.pnlCardDetected.Location = new System.Drawing.Point(3, 108);
            this.pnlCardDetected.Name = "pnlCardDetected";
            this.pnlCardDetected.Size = new System.Drawing.Size(207, 241);
            this.pnlCardDetected.TabIndex = 36;
            // 
            // lblRecentTrackCaption
            // 
            this.lblRecentTrackCaption.Location = new System.Drawing.Point(3, 216);
            this.lblRecentTrackCaption.Name = "lblRecentTrackCaption";
            this.lblRecentTrackCaption.Size = new System.Drawing.Size(81, 13);
            this.lblRecentTrackCaption.TabIndex = 42;
            this.lblRecentTrackCaption.Text = "Recent Track:";
            this.lblRecentTrackCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblRecentTrack
            // 
            this.lblRecentTrack.AutoSize = true;
            this.lblRecentTrack.Location = new System.Drawing.Point(90, 216);
            this.lblRecentTrack.Name = "lblRecentTrack";
            this.lblRecentTrack.Size = new System.Drawing.Size(41, 13);
            this.lblRecentTrack.TabIndex = 43;
            this.lblRecentTrack.Text = "label12";
            // 
            // lblRecentFolderCaption
            // 
            this.lblRecentFolderCaption.Location = new System.Drawing.Point(3, 193);
            this.lblRecentFolderCaption.Name = "lblRecentFolderCaption";
            this.lblRecentFolderCaption.Size = new System.Drawing.Size(81, 13);
            this.lblRecentFolderCaption.TabIndex = 40;
            this.lblRecentFolderCaption.Text = "Recent Folder:";
            this.lblRecentFolderCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblRecentFolder
            // 
            this.lblRecentFolder.AutoSize = true;
            this.lblRecentFolder.Location = new System.Drawing.Point(90, 193);
            this.lblRecentFolder.Name = "lblRecentFolder";
            this.lblRecentFolder.Size = new System.Drawing.Size(41, 13);
            this.lblRecentFolder.TabIndex = 41;
            this.lblRecentFolder.Text = "label12";
            // 
            // lblEndFolderCaption
            // 
            this.lblEndFolderCaption.Location = new System.Drawing.Point(3, 170);
            this.lblEndFolderCaption.Name = "lblEndFolderCaption";
            this.lblEndFolderCaption.Size = new System.Drawing.Size(80, 13);
            this.lblEndFolderCaption.TabIndex = 38;
            this.lblEndFolderCaption.Text = "End Folder:";
            this.lblEndFolderCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblEndFolder
            // 
            this.lblEndFolder.AutoSize = true;
            this.lblEndFolder.Location = new System.Drawing.Point(90, 170);
            this.lblEndFolder.Name = "lblEndFolder";
            this.lblEndFolder.Size = new System.Drawing.Size(41, 13);
            this.lblEndFolder.TabIndex = 39;
            this.lblEndFolder.Text = "label12";
            // 
            // lblHex
            // 
            this.lblHex.AutoSize = true;
            this.lblHex.Location = new System.Drawing.Point(66, 23);
            this.lblHex.Name = "lblHex";
            this.lblHex.Size = new System.Drawing.Size(35, 13);
            this.lblHex.TabIndex = 37;
            this.lblHex.Text = "label4";
            // 
            // lblHexCaption
            // 
            this.lblHexCaption.Location = new System.Drawing.Point(20, 23);
            this.lblHexCaption.Name = "lblHexCaption";
            this.lblHexCaption.Size = new System.Drawing.Size(45, 13);
            this.lblHexCaption.TabIndex = 36;
            this.lblHexCaption.Text = "Hex:";
            this.lblHexCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblReadModiValueCaption
            // 
            this.lblReadModiValueCaption.Location = new System.Drawing.Point(4, 74);
            this.lblReadModiValueCaption.Name = "lblReadModiValueCaption";
            this.lblReadModiValueCaption.Size = new System.Drawing.Size(80, 13);
            this.lblReadModiValueCaption.TabIndex = 34;
            this.lblReadModiValueCaption.Text = "Value:";
            this.lblReadModiValueCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblReadModiValue
            // 
            this.lblReadModiValue.AutoSize = true;
            this.lblReadModiValue.Location = new System.Drawing.Point(90, 74);
            this.lblReadModiValue.Name = "lblReadModiValue";
            this.lblReadModiValue.Size = new System.Drawing.Size(41, 13);
            this.lblReadModiValue.TabIndex = 35;
            this.lblReadModiValue.Text = "label10";
            // 
            // pnlModiCardAction
            // 
            this.pnlModiCardAction.Controls.Add(this.pnlModeBehaviour);
            this.pnlModiCardAction.Controls.Add(this.lblModeBehaviour);
            this.pnlModiCardAction.Controls.Add(this.lblMinutes);
            this.pnlModiCardAction.Controls.Add(this.lblModiValue);
            this.pnlModiCardAction.Controls.Add(this.textBox_ModiValue);
            this.pnlModiCardAction.Controls.Add(this.pnlModeCardOptions);
            this.pnlModiCardAction.Controls.Add(this.btnWriteModiCard);
            this.pnlModiCardAction.Location = new System.Drawing.Point(435, 139);
            this.pnlModiCardAction.Name = "pnlModiCardAction";
            this.pnlModiCardAction.Size = new System.Drawing.Size(203, 210);
            this.pnlModiCardAction.TabIndex = 39;
            // 
            // pnlModeBehaviour
            // 
            this.pnlModeBehaviour.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlModeBehaviour.Controls.Add(this.comboBox_ModiBehaviour);
            this.pnlModeBehaviour.Location = new System.Drawing.Point(9, 110);
            this.pnlModeBehaviour.Name = "pnlModeBehaviour";
            this.pnlModeBehaviour.Size = new System.Drawing.Size(175, 23);
            this.pnlModeBehaviour.TabIndex = 33;
            // 
            // comboBox_ModiBehaviour
            // 
            this.comboBox_ModiBehaviour.BackColor = System.Drawing.SystemColors.Window;
            this.comboBox_ModiBehaviour.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox_ModiBehaviour.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_ModiBehaviour.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.comboBox_ModiBehaviour.FormattingEnabled = true;
            this.comboBox_ModiBehaviour.Location = new System.Drawing.Point(0, 0);
            this.comboBox_ModiBehaviour.Name = "comboBox_ModiBehaviour";
            this.comboBox_ModiBehaviour.Size = new System.Drawing.Size(173, 21);
            this.comboBox_ModiBehaviour.TabIndex = 16;
            // 
            // lblModeBehaviour
            // 
            this.lblModeBehaviour.Location = new System.Drawing.Point(9, 91);
            this.lblModeBehaviour.Name = "lblModeBehaviour";
            this.lblModeBehaviour.Size = new System.Drawing.Size(58, 13);
            this.lblModeBehaviour.TabIndex = 32;
            this.lblModeBehaviour.Text = "Behaviour:";
            this.lblModeBehaviour.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblMinutes
            // 
            this.lblMinutes.AutoSize = true;
            this.lblMinutes.Location = new System.Drawing.Point(138, 62);
            this.lblMinutes.Name = "lblMinutes";
            this.lblMinutes.Size = new System.Drawing.Size(23, 13);
            this.lblMinutes.TabIndex = 31;
            this.lblMinutes.Text = "min";
            // 
            // lblModiValue
            // 
            this.lblModiValue.Location = new System.Drawing.Point(14, 62);
            this.lblModiValue.Name = "lblModiValue";
            this.lblModiValue.Size = new System.Drawing.Size(59, 13);
            this.lblModiValue.TabIndex = 29;
            this.lblModiValue.Text = "Value:";
            this.lblModiValue.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBox_ModiValue
            // 
            this.textBox_ModiValue.Location = new System.Drawing.Point(78, 59);
            this.textBox_ModiValue.MaxLength = 3;
            this.textBox_ModiValue.Name = "textBox_ModiValue";
            this.textBox_ModiValue.Size = new System.Drawing.Size(54, 20);
            this.textBox_ModiValue.TabIndex = 30;
            this.textBox_ModiValue.TextChanged += new System.EventHandler(this.textBoxSetting_ModiValue_TextChanged);
            // 
            // pnlModeCardOptions
            // 
            this.pnlModeCardOptions.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlModeCardOptions.Controls.Add(this.comboBox_ModiCardOptions);
            this.pnlModeCardOptions.Location = new System.Drawing.Point(9, 23);
            this.pnlModeCardOptions.Name = "pnlModeCardOptions";
            this.pnlModeCardOptions.Size = new System.Drawing.Size(175, 23);
            this.pnlModeCardOptions.TabIndex = 27;
            // 
            // comboBox_ModiCardOptions
            // 
            this.comboBox_ModiCardOptions.BackColor = System.Drawing.SystemColors.Window;
            this.comboBox_ModiCardOptions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox_ModiCardOptions.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_ModiCardOptions.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.comboBox_ModiCardOptions.FormattingEnabled = true;
            this.comboBox_ModiCardOptions.Location = new System.Drawing.Point(0, 0);
            this.comboBox_ModiCardOptions.Name = "comboBox_ModiCardOptions";
            this.comboBox_ModiCardOptions.Size = new System.Drawing.Size(173, 21);
            this.comboBox_ModiCardOptions.TabIndex = 16;
            this.comboBox_ModiCardOptions.SelectedIndexChanged += new System.EventHandler(this.comboBox_ModiCardOptions_SelectedIndexChanged);
            // 
            // btnWriteModiCard
            // 
            this.btnWriteModiCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.btnWriteModiCard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnWriteModiCard.Location = new System.Drawing.Point(9, 177);
            this.btnWriteModiCard.Name = "btnWriteModiCard";
            this.btnWriteModiCard.Size = new System.Drawing.Size(175, 23);
            this.btnWriteModiCard.TabIndex = 24;
            this.btnWriteModiCard.Text = "Write Modification Card";
            this.btnWriteModiCard.UseVisualStyleBackColor = false;
            this.btnWriteModiCard.Click += new System.EventHandler(this.btnWriteModiCard_Click);
            // 
            // pnlMusicCardAction
            // 
            this.pnlMusicCardAction.Controls.Add(this.lblWriteEndFolder);
            this.pnlMusicCardAction.Controls.Add(this.textBoxEndFolder);
            this.pnlMusicCardAction.Controls.Add(this.lblWriteStartFolder);
            this.pnlMusicCardAction.Controls.Add(this.lblStartOnSource);
            this.pnlMusicCardAction.Controls.Add(this.textBoxStartFolder);
            this.pnlMusicCardAction.Controls.Add(this.textBoxStartOnSD);
            this.pnlMusicCardAction.Controls.Add(this.lblEndOnSource);
            this.pnlMusicCardAction.Controls.Add(this.pnlModes);
            this.pnlMusicCardAction.Controls.Add(this.textBoxEndOnSD);
            this.pnlMusicCardAction.Controls.Add(this.btnWriteMusicCard);
            this.pnlMusicCardAction.Location = new System.Drawing.Point(215, 139);
            this.pnlMusicCardAction.Name = "pnlMusicCardAction";
            this.pnlMusicCardAction.Size = new System.Drawing.Size(210, 210);
            this.pnlMusicCardAction.TabIndex = 40;
            // 
            // lblWriteEndFolder
            // 
            this.lblWriteEndFolder.AutoSize = true;
            this.lblWriteEndFolder.Location = new System.Drawing.Point(68, 141);
            this.lblWriteEndFolder.Name = "lblWriteEndFolder";
            this.lblWriteEndFolder.Size = new System.Drawing.Size(54, 13);
            this.lblWriteEndFolder.TabIndex = 28;
            this.lblWriteEndFolder.Text = "end folder";
            // 
            // textBoxEndFolder
            // 
            this.textBoxEndFolder.Location = new System.Drawing.Point(9, 138);
            this.textBoxEndFolder.MaxLength = 3;
            this.textBoxEndFolder.Name = "textBoxEndFolder";
            this.textBoxEndFolder.Size = new System.Drawing.Size(53, 20);
            this.textBoxEndFolder.TabIndex = 29;
            this.textBoxEndFolder.TextChanged += new System.EventHandler(this.textBoxEndFolder_TextChanged);
            // 
            // radio_MusicCard
            // 
            this.radio_MusicCard.AutoSize = true;
            this.radio_MusicCard.Checked = true;
            this.radio_MusicCard.Location = new System.Drawing.Point(12, 3);
            this.radio_MusicCard.Name = "radio_MusicCard";
            this.radio_MusicCard.Size = new System.Drawing.Size(53, 17);
            this.radio_MusicCard.TabIndex = 41;
            this.radio_MusicCard.TabStop = true;
            this.radio_MusicCard.Text = "Music";
            this.radio_MusicCard.UseVisualStyleBackColor = true;
            this.radio_MusicCard.CheckedChanged += new System.EventHandler(this.radio_Card_CheckedChanged);
            // 
            // radio_ModiCard
            // 
            this.radio_ModiCard.AutoSize = true;
            this.radio_ModiCard.Location = new System.Drawing.Point(70, 3);
            this.radio_ModiCard.Name = "radio_ModiCard";
            this.radio_ModiCard.Size = new System.Drawing.Size(82, 17);
            this.radio_ModiCard.TabIndex = 42;
            this.radio_ModiCard.Text = "Modification";
            this.radio_ModiCard.UseVisualStyleBackColor = true;
            this.radio_ModiCard.CheckedChanged += new System.EventHandler(this.radio_Card_CheckedChanged);
            // 
            // pnlCardAction
            // 
            this.pnlCardAction.Controls.Add(this.radio_Raw);
            this.pnlCardAction.Controls.Add(this.radio_MusicCard);
            this.pnlCardAction.Controls.Add(this.radio_ModiCard);
            this.pnlCardAction.Location = new System.Drawing.Point(215, 108);
            this.pnlCardAction.Name = "pnlCardAction";
            this.pnlCardAction.Size = new System.Drawing.Size(210, 28);
            this.pnlCardAction.TabIndex = 43;
            // 
            // radio_Raw
            // 
            this.radio_Raw.AutoSize = true;
            this.radio_Raw.Location = new System.Drawing.Point(152, 3);
            this.radio_Raw.Name = "radio_Raw";
            this.radio_Raw.Size = new System.Drawing.Size(47, 17);
            this.radio_Raw.TabIndex = 43;
            this.radio_Raw.Text = "Raw";
            this.radio_Raw.UseVisualStyleBackColor = true;
            // 
            // pnlSeparator
            // 
            this.pnlSeparator.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.pnlSeparator.Location = new System.Drawing.Point(212, 61);
            this.pnlSeparator.Name = "pnlSeparator";
            this.pnlSeparator.Size = new System.Drawing.Size(1, 320);
            this.pnlSeparator.TabIndex = 44;
            // 
            // pnlPorts
            // 
            this.pnlPorts.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlPorts.Controls.Add(this.comboBox_Ports);
            this.pnlPorts.Location = new System.Drawing.Point(75, 18);
            this.pnlPorts.Name = "pnlPorts";
            this.pnlPorts.Size = new System.Drawing.Size(86, 23);
            this.pnlPorts.TabIndex = 46;
            // 
            // comboBox_Ports
            // 
            this.comboBox_Ports.BackColor = System.Drawing.SystemColors.Window;
            this.comboBox_Ports.Dock = System.Windows.Forms.DockStyle.Fill;
            this.comboBox_Ports.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_Ports.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.comboBox_Ports.FormattingEnabled = true;
            this.comboBox_Ports.Location = new System.Drawing.Point(0, 0);
            this.comboBox_Ports.Name = "comboBox_Ports";
            this.comboBox_Ports.Size = new System.Drawing.Size(84, 21);
            this.comboBox_Ports.TabIndex = 16;
            // 
            // lblPorts
            // 
            this.lblPorts.AutoSize = true;
            this.lblPorts.Location = new System.Drawing.Point(12, 23);
            this.lblPorts.Name = "lblPorts";
            this.lblPorts.Size = new System.Drawing.Size(61, 13);
            this.lblPorts.TabIndex = 45;
            this.lblPorts.Text = "COM Ports:";
            this.lblPorts.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // btnResetCard
            // 
            this.btnResetCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.btnResetCard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnResetCard.Location = new System.Drawing.Point(224, 355);
            this.btnResetCard.Name = "btnResetCard";
            this.btnResetCard.Size = new System.Drawing.Size(175, 23);
            this.btnResetCard.TabIndex = 47;
            this.btnResetCard.Text = "Reset Card";
            this.btnResetCard.UseVisualStyleBackColor = false;
            this.btnResetCard.Click += new System.EventHandler(this.btnResetCard_Click);
            // 
            // lblRead
            // 
            this.lblRead.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.lblRead.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblRead.ForeColor = System.Drawing.Color.White;
            this.lblRead.Location = new System.Drawing.Point(3, 61);
            this.lblRead.Name = "lblRead";
            this.lblRead.Size = new System.Drawing.Size(207, 22);
            this.lblRead.TabIndex = 48;
            this.lblRead.Text = "READ";
            this.lblRead.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(215, 61);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(211, 22);
            this.label1.TabIndex = 49;
            this.label1.Text = "WRITE";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pnlRawDataAction
            // 
            this.pnlRawDataAction.Controls.Add(this.lblByte15);
            this.pnlRawDataAction.Controls.Add(this.boxByte15);
            this.pnlRawDataAction.Controls.Add(this.lblByte14);
            this.pnlRawDataAction.Controls.Add(this.boxByte14);
            this.pnlRawDataAction.Controls.Add(this.lblByte13);
            this.pnlRawDataAction.Controls.Add(this.boxByte13);
            this.pnlRawDataAction.Controls.Add(this.lblByte12);
            this.pnlRawDataAction.Controls.Add(this.boxByte12);
            this.pnlRawDataAction.Controls.Add(this.lblByte11);
            this.pnlRawDataAction.Controls.Add(this.boxByte11);
            this.pnlRawDataAction.Controls.Add(this.lblByte10);
            this.pnlRawDataAction.Controls.Add(this.boxByte10);
            this.pnlRawDataAction.Controls.Add(this.lblByte09);
            this.pnlRawDataAction.Controls.Add(this.boxByte09);
            this.pnlRawDataAction.Controls.Add(this.lblByte08);
            this.pnlRawDataAction.Controls.Add(this.boxByte08);
            this.pnlRawDataAction.Controls.Add(this.lblByte07);
            this.pnlRawDataAction.Controls.Add(this.boxByte07);
            this.pnlRawDataAction.Controls.Add(this.lblByte06);
            this.pnlRawDataAction.Controls.Add(this.boxByte06);
            this.pnlRawDataAction.Controls.Add(this.lblByte05);
            this.pnlRawDataAction.Controls.Add(this.boxByte05);
            this.pnlRawDataAction.Controls.Add(this.lblByte04);
            this.pnlRawDataAction.Controls.Add(this.boxByte04);
            this.pnlRawDataAction.Controls.Add(this.lblByte03);
            this.pnlRawDataAction.Controls.Add(this.boxByte03);
            this.pnlRawDataAction.Controls.Add(this.lblByte02);
            this.pnlRawDataAction.Controls.Add(this.boxByte02);
            this.pnlRawDataAction.Controls.Add(this.lblByte01);
            this.pnlRawDataAction.Controls.Add(this.boxByte01);
            this.pnlRawDataAction.Controls.Add(this.btnWriteRawCard);
            this.pnlRawDataAction.Location = new System.Drawing.Point(573, 18);
            this.pnlRawDataAction.Name = "pnlRawDataAction";
            this.pnlRawDataAction.Size = new System.Drawing.Size(203, 210);
            this.pnlRawDataAction.TabIndex = 50;
            // 
            // lblByte15
            // 
            this.lblByte15.Location = new System.Drawing.Point(155, 115);
            this.lblByte15.Name = "lblByte15";
            this.lblByte15.Size = new System.Drawing.Size(30, 13);
            this.lblByte15.TabIndex = 57;
            this.lblByte15.Text = "15";
            this.lblByte15.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte15
            // 
            this.boxByte15.Location = new System.Drawing.Point(155, 129);
            this.boxByte15.MaxLength = 3;
            this.boxByte15.Name = "boxByte15";
            this.boxByte15.Size = new System.Drawing.Size(30, 20);
            this.boxByte15.TabIndex = 58;
            this.boxByte15.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte14
            // 
            this.lblByte14.Location = new System.Drawing.Point(119, 115);
            this.lblByte14.Name = "lblByte14";
            this.lblByte14.Size = new System.Drawing.Size(30, 13);
            this.lblByte14.TabIndex = 55;
            this.lblByte14.Text = "14";
            this.lblByte14.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte14
            // 
            this.boxByte14.Location = new System.Drawing.Point(119, 129);
            this.boxByte14.MaxLength = 3;
            this.boxByte14.Name = "boxByte14";
            this.boxByte14.Size = new System.Drawing.Size(30, 20);
            this.boxByte14.TabIndex = 56;
            this.boxByte14.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte13
            // 
            this.lblByte13.Location = new System.Drawing.Point(83, 115);
            this.lblByte13.Name = "lblByte13";
            this.lblByte13.Size = new System.Drawing.Size(30, 13);
            this.lblByte13.TabIndex = 53;
            this.lblByte13.Text = "13";
            this.lblByte13.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte13
            // 
            this.boxByte13.Location = new System.Drawing.Point(83, 129);
            this.boxByte13.MaxLength = 3;
            this.boxByte13.Name = "boxByte13";
            this.boxByte13.Size = new System.Drawing.Size(30, 20);
            this.boxByte13.TabIndex = 54;
            this.boxByte13.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte12
            // 
            this.lblByte12.Location = new System.Drawing.Point(47, 115);
            this.lblByte12.Name = "lblByte12";
            this.lblByte12.Size = new System.Drawing.Size(30, 13);
            this.lblByte12.TabIndex = 51;
            this.lblByte12.Text = "12";
            this.lblByte12.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte12
            // 
            this.boxByte12.Location = new System.Drawing.Point(47, 129);
            this.boxByte12.MaxLength = 3;
            this.boxByte12.Name = "boxByte12";
            this.boxByte12.Size = new System.Drawing.Size(30, 20);
            this.boxByte12.TabIndex = 52;
            this.boxByte12.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte11
            // 
            this.lblByte11.Location = new System.Drawing.Point(11, 115);
            this.lblByte11.Name = "lblByte11";
            this.lblByte11.Size = new System.Drawing.Size(30, 13);
            this.lblByte11.TabIndex = 49;
            this.lblByte11.Text = "11";
            this.lblByte11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte11
            // 
            this.boxByte11.Location = new System.Drawing.Point(11, 129);
            this.boxByte11.MaxLength = 3;
            this.boxByte11.Name = "boxByte11";
            this.boxByte11.Size = new System.Drawing.Size(30, 20);
            this.boxByte11.TabIndex = 50;
            this.boxByte11.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte10
            // 
            this.lblByte10.Location = new System.Drawing.Point(154, 65);
            this.lblByte10.Name = "lblByte10";
            this.lblByte10.Size = new System.Drawing.Size(30, 13);
            this.lblByte10.TabIndex = 47;
            this.lblByte10.Text = "10";
            this.lblByte10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte10
            // 
            this.boxByte10.Location = new System.Drawing.Point(154, 79);
            this.boxByte10.MaxLength = 3;
            this.boxByte10.Name = "boxByte10";
            this.boxByte10.Size = new System.Drawing.Size(30, 20);
            this.boxByte10.TabIndex = 48;
            this.boxByte10.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte09
            // 
            this.lblByte09.Location = new System.Drawing.Point(119, 65);
            this.lblByte09.Name = "lblByte09";
            this.lblByte09.Size = new System.Drawing.Size(30, 13);
            this.lblByte09.TabIndex = 45;
            this.lblByte09.Text = "09";
            this.lblByte09.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte09
            // 
            this.boxByte09.Location = new System.Drawing.Point(119, 79);
            this.boxByte09.MaxLength = 3;
            this.boxByte09.Name = "boxByte09";
            this.boxByte09.Size = new System.Drawing.Size(30, 20);
            this.boxByte09.TabIndex = 46;
            this.boxByte09.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte08
            // 
            this.lblByte08.Location = new System.Drawing.Point(83, 65);
            this.lblByte08.Name = "lblByte08";
            this.lblByte08.Size = new System.Drawing.Size(30, 13);
            this.lblByte08.TabIndex = 43;
            this.lblByte08.Text = "08";
            this.lblByte08.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte08
            // 
            this.boxByte08.Location = new System.Drawing.Point(83, 79);
            this.boxByte08.MaxLength = 3;
            this.boxByte08.Name = "boxByte08";
            this.boxByte08.Size = new System.Drawing.Size(30, 20);
            this.boxByte08.TabIndex = 44;
            this.boxByte08.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte07
            // 
            this.lblByte07.Location = new System.Drawing.Point(47, 65);
            this.lblByte07.Name = "lblByte07";
            this.lblByte07.Size = new System.Drawing.Size(30, 13);
            this.lblByte07.TabIndex = 41;
            this.lblByte07.Text = "07";
            this.lblByte07.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte07
            // 
            this.boxByte07.Location = new System.Drawing.Point(47, 79);
            this.boxByte07.MaxLength = 3;
            this.boxByte07.Name = "boxByte07";
            this.boxByte07.Size = new System.Drawing.Size(30, 20);
            this.boxByte07.TabIndex = 42;
            this.boxByte07.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte06
            // 
            this.lblByte06.Location = new System.Drawing.Point(11, 65);
            this.lblByte06.Name = "lblByte06";
            this.lblByte06.Size = new System.Drawing.Size(30, 13);
            this.lblByte06.TabIndex = 39;
            this.lblByte06.Text = "06";
            this.lblByte06.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte06
            // 
            this.boxByte06.Location = new System.Drawing.Point(11, 79);
            this.boxByte06.MaxLength = 3;
            this.boxByte06.Name = "boxByte06";
            this.boxByte06.Size = new System.Drawing.Size(30, 20);
            this.boxByte06.TabIndex = 40;
            this.boxByte06.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte05
            // 
            this.lblByte05.Location = new System.Drawing.Point(154, 15);
            this.lblByte05.Name = "lblByte05";
            this.lblByte05.Size = new System.Drawing.Size(30, 13);
            this.lblByte05.TabIndex = 37;
            this.lblByte05.Text = "05";
            this.lblByte05.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte05
            // 
            this.boxByte05.Location = new System.Drawing.Point(154, 29);
            this.boxByte05.MaxLength = 3;
            this.boxByte05.Name = "boxByte05";
            this.boxByte05.Size = new System.Drawing.Size(30, 20);
            this.boxByte05.TabIndex = 38;
            this.boxByte05.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte04
            // 
            this.lblByte04.Location = new System.Drawing.Point(119, 15);
            this.lblByte04.Name = "lblByte04";
            this.lblByte04.Size = new System.Drawing.Size(30, 13);
            this.lblByte04.TabIndex = 35;
            this.lblByte04.Text = "04";
            this.lblByte04.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte04
            // 
            this.boxByte04.Location = new System.Drawing.Point(119, 29);
            this.boxByte04.MaxLength = 3;
            this.boxByte04.Name = "boxByte04";
            this.boxByte04.Size = new System.Drawing.Size(30, 20);
            this.boxByte04.TabIndex = 36;
            this.boxByte04.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte03
            // 
            this.lblByte03.Location = new System.Drawing.Point(83, 15);
            this.lblByte03.Name = "lblByte03";
            this.lblByte03.Size = new System.Drawing.Size(30, 13);
            this.lblByte03.TabIndex = 33;
            this.lblByte03.Text = "03";
            this.lblByte03.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte03
            // 
            this.boxByte03.Location = new System.Drawing.Point(83, 29);
            this.boxByte03.MaxLength = 3;
            this.boxByte03.Name = "boxByte03";
            this.boxByte03.Size = new System.Drawing.Size(30, 20);
            this.boxByte03.TabIndex = 34;
            this.boxByte03.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte02
            // 
            this.lblByte02.Location = new System.Drawing.Point(47, 15);
            this.lblByte02.Name = "lblByte02";
            this.lblByte02.Size = new System.Drawing.Size(30, 13);
            this.lblByte02.TabIndex = 31;
            this.lblByte02.Text = "02";
            this.lblByte02.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte02
            // 
            this.boxByte02.Location = new System.Drawing.Point(47, 29);
            this.boxByte02.MaxLength = 3;
            this.boxByte02.Name = "boxByte02";
            this.boxByte02.Size = new System.Drawing.Size(30, 20);
            this.boxByte02.TabIndex = 32;
            this.boxByte02.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // lblByte01
            // 
            this.lblByte01.Location = new System.Drawing.Point(11, 15);
            this.lblByte01.Name = "lblByte01";
            this.lblByte01.Size = new System.Drawing.Size(30, 13);
            this.lblByte01.TabIndex = 29;
            this.lblByte01.Text = "01";
            this.lblByte01.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // boxByte01
            // 
            this.boxByte01.Location = new System.Drawing.Point(11, 29);
            this.boxByte01.MaxLength = 3;
            this.boxByte01.Name = "boxByte01";
            this.boxByte01.Size = new System.Drawing.Size(30, 20);
            this.boxByte01.TabIndex = 30;
            this.boxByte01.TextChanged += new System.EventHandler(this.boxByte_TextChanged);
            // 
            // btnWriteRawCard
            // 
            this.btnWriteRawCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.btnWriteRawCard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnWriteRawCard.Location = new System.Drawing.Point(9, 177);
            this.btnWriteRawCard.Name = "btnWriteRawCard";
            this.btnWriteRawCard.Size = new System.Drawing.Size(175, 23);
            this.btnWriteRawCard.TabIndex = 24;
            this.btnWriteRawCard.Text = "Write Raw Card";
            this.btnWriteRawCard.UseVisualStyleBackColor = false;
            this.btnWriteRawCard.Click += new System.EventHandler(this.btnWriteRawCard_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(786, 409);
            this.Controls.Add(this.pnlRawDataAction);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblRead);
            this.Controls.Add(this.btnResetCard);
            this.Controls.Add(this.pnlPorts);
            this.Controls.Add(this.lblPorts);
            this.Controls.Add(this.pnlSeparator);
            this.Controls.Add(this.pnlCardAction);
            this.Controls.Add(this.pnlMusicCardAction);
            this.Controls.Add(this.pnlModiCardAction);
            this.Controls.Add(this.pnlCardDetected);
            this.Controls.Add(this.lblCardDetected);
            this.Controls.Add(this.logTextBox);
            this.Controls.Add(this.btnConnectPort);
            this.Controls.Add(this.lblConnectedPort);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "MainForm";
            this.Text = "Tonuino RFID Tool";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.pnlModes.ResumeLayout(false);
            this.pnlCardDetected.ResumeLayout(false);
            this.pnlCardDetected.PerformLayout();
            this.pnlModiCardAction.ResumeLayout(false);
            this.pnlModiCardAction.PerformLayout();
            this.pnlModeBehaviour.ResumeLayout(false);
            this.pnlModeCardOptions.ResumeLayout(false);
            this.pnlMusicCardAction.ResumeLayout(false);
            this.pnlMusicCardAction.PerformLayout();
            this.pnlCardAction.ResumeLayout(false);
            this.pnlCardAction.PerformLayout();
            this.pnlPorts.ResumeLayout(false);
            this.pnlRawDataAction.ResumeLayout(false);
            this.pnlRawDataAction.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label lblConnectedPort;
        private System.Windows.Forms.Button btnConnectPort;
        private System.Windows.Forms.RichTextBox logTextBox;
        private System.Windows.Forms.Label lblCardDetected;
        private System.Windows.Forms.Label lblRFIDCaption;
        private System.Windows.Forms.Label lblRFID;
        private System.Windows.Forms.Label lblModeCaption;
        private System.Windows.Forms.Label lblMode;
        private System.Windows.Forms.Label lblFolderCaption;
        private System.Windows.Forms.Label lblFolder;
        private System.Windows.Forms.Label lblStartPosCaption;
        private System.Windows.Forms.Label lblStartPos;
        private System.Windows.Forms.Label lblEndPosCaption;
        private System.Windows.Forms.Label lblEndPos;
        private Tonuino_RFID_Tool.ExtendedComboBox comboBox_MusicCardModes;
        private System.Windows.Forms.Label lblWriteStartFolder;
        private System.Windows.Forms.Label lblStartOnSource;
        private System.Windows.Forms.TextBox textBoxStartFolder;
        private System.Windows.Forms.TextBox textBoxStartOnSD;
        private System.Windows.Forms.TextBox textBoxEndOnSD;
        private System.Windows.Forms.Label lblEndOnSource;
        private System.Windows.Forms.Button btnWriteMusicCard;
        private System.Windows.Forms.Panel pnlModes;
        private System.Windows.Forms.Panel pnlCardDetected;
        private System.Windows.Forms.Panel pnlModiCardAction;
        private System.Windows.Forms.Label lblMinutes;
        private System.Windows.Forms.Label lblModiValue;
        private System.Windows.Forms.TextBox textBox_ModiValue;
        private System.Windows.Forms.Panel pnlModeCardOptions;
        private Tonuino_RFID_Tool.ExtendedComboBox comboBox_ModiCardOptions;
        private System.Windows.Forms.Button btnWriteModiCard;
        private System.Windows.Forms.Panel pnlMusicCardAction;
        private System.Windows.Forms.RadioButton radio_MusicCard;
        private System.Windows.Forms.RadioButton radio_ModiCard;
        private System.Windows.Forms.Panel pnlCardAction;
        private System.Windows.Forms.Panel pnlSeparator;
        private System.Windows.Forms.Panel pnlPorts;
        private Tonuino_RFID_Tool.ExtendedComboBox comboBox_Ports;
        private System.Windows.Forms.Label lblPorts;
        private System.Windows.Forms.Label lblReadModiValueCaption;
        private System.Windows.Forms.Label lblReadModiValue;
        private System.Windows.Forms.Panel pnlModeBehaviour;
        private ExtendedComboBox comboBox_ModiBehaviour;
        private System.Windows.Forms.Label lblModeBehaviour;
        private System.Windows.Forms.Button btnResetCard;
        private System.Windows.Forms.Label lblHex;
        private System.Windows.Forms.Label lblHexCaption;
        private System.Windows.Forms.RadioButton radio_Raw;
        private System.Windows.Forms.Label lblRead;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel pnlRawDataAction;
        private System.Windows.Forms.Label lblByte01;
        private System.Windows.Forms.TextBox boxByte01;
        private System.Windows.Forms.Button btnWriteRawCard;
        private System.Windows.Forms.Label lblByte15;
        private System.Windows.Forms.TextBox boxByte15;
        private System.Windows.Forms.Label lblByte14;
        private System.Windows.Forms.TextBox boxByte14;
        private System.Windows.Forms.Label lblByte13;
        private System.Windows.Forms.TextBox boxByte13;
        private System.Windows.Forms.Label lblByte12;
        private System.Windows.Forms.TextBox boxByte12;
        private System.Windows.Forms.Label lblByte11;
        private System.Windows.Forms.TextBox boxByte11;
        private System.Windows.Forms.Label lblByte10;
        private System.Windows.Forms.TextBox boxByte10;
        private System.Windows.Forms.Label lblByte09;
        private System.Windows.Forms.TextBox boxByte09;
        private System.Windows.Forms.Label lblByte08;
        private System.Windows.Forms.TextBox boxByte08;
        private System.Windows.Forms.Label lblByte07;
        private System.Windows.Forms.TextBox boxByte07;
        private System.Windows.Forms.Label lblByte06;
        private System.Windows.Forms.TextBox boxByte06;
        private System.Windows.Forms.Label lblByte05;
        private System.Windows.Forms.TextBox boxByte05;
        private System.Windows.Forms.Label lblByte04;
        private System.Windows.Forms.TextBox boxByte04;
        private System.Windows.Forms.Label lblByte03;
        private System.Windows.Forms.TextBox boxByte03;
        private System.Windows.Forms.Label lblByte02;
        private System.Windows.Forms.TextBox boxByte02;
        private System.Windows.Forms.Label lblEndFolderCaption;
        private System.Windows.Forms.Label lblEndFolder;
        private System.Windows.Forms.Label lblWriteEndFolder;
        private System.Windows.Forms.TextBox textBoxEndFolder;
        private System.Windows.Forms.Label lblRecentTrackCaption;
        private System.Windows.Forms.Label lblRecentTrack;
        private System.Windows.Forms.Label lblRecentFolderCaption;
        private System.Windows.Forms.Label lblRecentFolder;
    }
}

