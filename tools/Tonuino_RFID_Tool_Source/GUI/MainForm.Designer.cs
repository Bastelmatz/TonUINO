namespace Tonuino_RFID_Creator
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
            this.lblFolderOnSource = new System.Windows.Forms.Label();
            this.lblStartOnSource = new System.Windows.Forms.Label();
            this.textBoxFolderOnSD = new System.Windows.Forms.TextBox();
            this.textBoxStartOnSD = new System.Windows.Forms.TextBox();
            this.textBoxEndOnSD = new System.Windows.Forms.TextBox();
            this.lblEndOnSource = new System.Windows.Forms.Label();
            this.btnBrowsMusic = new System.Windows.Forms.Button();
            this.btnWriteMusicCard = new System.Windows.Forms.Button();
            this.checkExtendCard = new System.Windows.Forms.CheckBox();
            this.pnlModes = new System.Windows.Forms.Panel();
            this.comboBox_MusicCardModes = new Tonuino_RFID_Creator.ExtendedComboBox();
            this.lblComment = new System.Windows.Forms.Label();
            this.textBoxComment = new System.Windows.Forms.TextBox();
            this.lblLastCommentCaption = new System.Windows.Forms.Label();
            this.lblLastComment = new System.Windows.Forms.Label();
            this.pnlCardDetected = new System.Windows.Forms.Panel();
            this.lblReadModiValueCaption = new System.Windows.Forms.Label();
            this.lblReadModiValue = new System.Windows.Forms.Label();
            this.pnlModiCardAction = new System.Windows.Forms.Panel();
            this.pnlModeBehaviour = new System.Windows.Forms.Panel();
            this.comboBox_ModiBehaviour = new Tonuino_RFID_Creator.ExtendedComboBox();
            this.lblModeBehaviour = new System.Windows.Forms.Label();
            this.lblMinutes = new System.Windows.Forms.Label();
            this.lblModiValue = new System.Windows.Forms.Label();
            this.textBox_ModiValue = new System.Windows.Forms.TextBox();
            this.pnlModeCardOptions = new System.Windows.Forms.Panel();
            this.comboBox_ModiCardOptions = new Tonuino_RFID_Creator.ExtendedComboBox();
            this.btnWriteModiCard = new System.Windows.Forms.Button();
            this.pnlMusicCardAction = new System.Windows.Forms.Panel();
            this.radio_MusicCard = new System.Windows.Forms.RadioButton();
            this.radio_ModiCard = new System.Windows.Forms.RadioButton();
            this.pnlCardAction = new System.Windows.Forms.Panel();
            this.pnlSeparator = new System.Windows.Forms.Panel();
            this.pnlPorts = new System.Windows.Forms.Panel();
            this.comboBox_Ports = new Tonuino_RFID_Creator.ExtendedComboBox();
            this.lblPorts = new System.Windows.Forms.Label();
            this.pnlModes.SuspendLayout();
            this.pnlCardDetected.SuspendLayout();
            this.pnlModiCardAction.SuspendLayout();
            this.pnlModeBehaviour.SuspendLayout();
            this.pnlModeCardOptions.SuspendLayout();
            this.pnlMusicCardAction.SuspendLayout();
            this.pnlCardAction.SuspendLayout();
            this.pnlPorts.SuspendLayout();
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
            this.logTextBox.Location = new System.Drawing.Point(425, 12);
            this.logTextBox.Name = "logTextBox";
            this.logTextBox.ReadOnly = true;
            this.logTextBox.Size = new System.Drawing.Size(349, 573);
            this.logTextBox.TabIndex = 4;
            this.logTextBox.Text = "";
            // 
            // lblCardDetected
            // 
            this.lblCardDetected.AutoSize = true;
            this.lblCardDetected.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCardDetected.Location = new System.Drawing.Point(22, 56);
            this.lblCardDetected.Name = "lblCardDetected";
            this.lblCardDetected.Size = new System.Drawing.Size(94, 16);
            this.lblCardDetected.TabIndex = 5;
            this.lblCardDetected.Text = "Current Card";
            // 
            // lblRFIDCaption
            // 
            this.lblRFIDCaption.Location = new System.Drawing.Point(9, 6);
            this.lblRFIDCaption.Name = "lblRFIDCaption";
            this.lblRFIDCaption.Size = new System.Drawing.Size(45, 13);
            this.lblRFIDCaption.TabIndex = 6;
            this.lblRFIDCaption.Text = "RFID:";
            this.lblRFIDCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblRFID
            // 
            this.lblRFID.AutoSize = true;
            this.lblRFID.Location = new System.Drawing.Point(60, 6);
            this.lblRFID.Name = "lblRFID";
            this.lblRFID.Size = new System.Drawing.Size(35, 13);
            this.lblRFID.TabIndex = 7;
            this.lblRFID.Text = "label4";
            // 
            // lblModeCaption
            // 
            this.lblModeCaption.Location = new System.Drawing.Point(3, 60);
            this.lblModeCaption.Name = "lblModeCaption";
            this.lblModeCaption.Size = new System.Drawing.Size(70, 13);
            this.lblModeCaption.TabIndex = 8;
            this.lblModeCaption.Text = "Mode:";
            this.lblModeCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblMode
            // 
            this.lblMode.AutoSize = true;
            this.lblMode.Location = new System.Drawing.Point(78, 60);
            this.lblMode.Name = "lblMode";
            this.lblMode.Size = new System.Drawing.Size(35, 13);
            this.lblMode.TabIndex = 9;
            this.lblMode.Text = "label6";
            // 
            // lblFolderCaption
            // 
            this.lblFolderCaption.Location = new System.Drawing.Point(2, 122);
            this.lblFolderCaption.Name = "lblFolderCaption";
            this.lblFolderCaption.Size = new System.Drawing.Size(70, 13);
            this.lblFolderCaption.TabIndex = 10;
            this.lblFolderCaption.Text = "Folder:";
            this.lblFolderCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblFolder
            // 
            this.lblFolder.AutoSize = true;
            this.lblFolder.Location = new System.Drawing.Point(78, 122);
            this.lblFolder.Name = "lblFolder";
            this.lblFolder.Size = new System.Drawing.Size(35, 13);
            this.lblFolder.TabIndex = 11;
            this.lblFolder.Text = "label8";
            // 
            // lblStartPosCaption
            // 
            this.lblStartPosCaption.Location = new System.Drawing.Point(2, 147);
            this.lblStartPosCaption.Name = "lblStartPosCaption";
            this.lblStartPosCaption.Size = new System.Drawing.Size(70, 13);
            this.lblStartPosCaption.TabIndex = 12;
            this.lblStartPosCaption.Text = "Start Track:";
            this.lblStartPosCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblStartPos
            // 
            this.lblStartPos.AutoSize = true;
            this.lblStartPos.Location = new System.Drawing.Point(78, 147);
            this.lblStartPos.Name = "lblStartPos";
            this.lblStartPos.Size = new System.Drawing.Size(41, 13);
            this.lblStartPos.TabIndex = 13;
            this.lblStartPos.Text = "label10";
            // 
            // lblEndPosCaption
            // 
            this.lblEndPosCaption.Location = new System.Drawing.Point(2, 173);
            this.lblEndPosCaption.Name = "lblEndPosCaption";
            this.lblEndPosCaption.Size = new System.Drawing.Size(70, 13);
            this.lblEndPosCaption.TabIndex = 14;
            this.lblEndPosCaption.Text = "End Track:";
            this.lblEndPosCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblEndPos
            // 
            this.lblEndPos.AutoSize = true;
            this.lblEndPos.Location = new System.Drawing.Point(78, 173);
            this.lblEndPos.Name = "lblEndPos";
            this.lblEndPos.Size = new System.Drawing.Size(41, 13);
            this.lblEndPos.TabIndex = 15;
            this.lblEndPos.Text = "label12";
            // 
            // lblFolderOnSource
            // 
            this.lblFolderOnSource.AutoSize = true;
            this.lblFolderOnSource.Location = new System.Drawing.Point(72, 91);
            this.lblFolderOnSource.Name = "lblFolderOnSource";
            this.lblFolderOnSource.Size = new System.Drawing.Size(33, 13);
            this.lblFolderOnSource.TabIndex = 17;
            this.lblFolderOnSource.Text = "folder";
            // 
            // lblStartOnSource
            // 
            this.lblStartOnSource.AutoSize = true;
            this.lblStartOnSource.Location = new System.Drawing.Point(72, 116);
            this.lblStartOnSource.Name = "lblStartOnSource";
            this.lblStartOnSource.Size = new System.Drawing.Size(54, 13);
            this.lblStartOnSource.TabIndex = 18;
            this.lblStartOnSource.Text = "start track";
            // 
            // textBoxFolderOnSD
            // 
            this.textBoxFolderOnSD.Location = new System.Drawing.Point(13, 88);
            this.textBoxFolderOnSD.MaxLength = 2;
            this.textBoxFolderOnSD.Name = "textBoxFolderOnSD";
            this.textBoxFolderOnSD.Size = new System.Drawing.Size(53, 20);
            this.textBoxFolderOnSD.TabIndex = 19;
            this.textBoxFolderOnSD.TextChanged += new System.EventHandler(this.textBoxFolderOnSD_TextChanged);
            // 
            // textBoxStartOnSD
            // 
            this.textBoxStartOnSD.Location = new System.Drawing.Point(13, 113);
            this.textBoxStartOnSD.MaxLength = 3;
            this.textBoxStartOnSD.Name = "textBoxStartOnSD";
            this.textBoxStartOnSD.Size = new System.Drawing.Size(53, 20);
            this.textBoxStartOnSD.TabIndex = 20;
            this.textBoxStartOnSD.TextChanged += new System.EventHandler(this.textBoxStartOnSD_TextChanged);
            // 
            // textBoxEndOnSD
            // 
            this.textBoxEndOnSD.Location = new System.Drawing.Point(13, 139);
            this.textBoxEndOnSD.MaxLength = 3;
            this.textBoxEndOnSD.Name = "textBoxEndOnSD";
            this.textBoxEndOnSD.Size = new System.Drawing.Size(53, 20);
            this.textBoxEndOnSD.TabIndex = 22;
            this.textBoxEndOnSD.TextChanged += new System.EventHandler(this.textBoxEndOnSD_TextChanged);
            // 
            // lblEndOnSource
            // 
            this.lblEndOnSource.AutoSize = true;
            this.lblEndOnSource.Location = new System.Drawing.Point(72, 142);
            this.lblEndOnSource.Name = "lblEndOnSource";
            this.lblEndOnSource.Size = new System.Drawing.Size(52, 13);
            this.lblEndOnSource.TabIndex = 21;
            this.lblEndOnSource.Text = "end track";
            // 
            // btnBrowsMusic
            // 
            this.btnBrowsMusic.Location = new System.Drawing.Point(13, 52);
            this.btnBrowsMusic.Name = "btnBrowsMusic";
            this.btnBrowsMusic.Size = new System.Drawing.Size(158, 23);
            this.btnBrowsMusic.TabIndex = 23;
            this.btnBrowsMusic.Text = "Browse for music";
            this.btnBrowsMusic.UseVisualStyleBackColor = true;
            // 
            // btnWriteMusicCard
            // 
            this.btnWriteMusicCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.btnWriteMusicCard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnWriteMusicCard.Location = new System.Drawing.Point(13, 220);
            this.btnWriteMusicCard.Name = "btnWriteMusicCard";
            this.btnWriteMusicCard.Size = new System.Drawing.Size(158, 23);
            this.btnWriteMusicCard.TabIndex = 24;
            this.btnWriteMusicCard.Text = "Write Music Card";
            this.btnWriteMusicCard.UseVisualStyleBackColor = false;
            this.btnWriteMusicCard.Click += new System.EventHandler(this.btnWriteMusicCard_Click);
            // 
            // checkExtendCard
            // 
            this.checkExtendCard.AutoSize = true;
            this.checkExtendCard.Location = new System.Drawing.Point(14, 3);
            this.checkExtendCard.Name = "checkExtendCard";
            this.checkExtendCard.Size = new System.Drawing.Size(122, 17);
            this.checkExtendCard.TabIndex = 26;
            this.checkExtendCard.Text = "Extend card content";
            this.checkExtendCard.UseVisualStyleBackColor = true;
            this.checkExtendCard.Visible = false;
            // 
            // pnlModes
            // 
            this.pnlModes.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlModes.Controls.Add(this.comboBox_MusicCardModes);
            this.pnlModes.Location = new System.Drawing.Point(13, 23);
            this.pnlModes.Name = "pnlModes";
            this.pnlModes.Size = new System.Drawing.Size(158, 23);
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
            this.comboBox_MusicCardModes.Size = new System.Drawing.Size(156, 21);
            this.comboBox_MusicCardModes.TabIndex = 16;
            this.comboBox_MusicCardModes.SelectedValueChanged += new System.EventHandler(this.comboBoxCardModes_SelectedValueChanged);
            // 
            // lblComment
            // 
            this.lblComment.AutoSize = true;
            this.lblComment.Location = new System.Drawing.Point(13, 166);
            this.lblComment.Name = "lblComment";
            this.lblComment.Size = new System.Drawing.Size(143, 13);
            this.lblComment.TabIndex = 28;
            this.lblComment.Text = "Optional comment for history:";
            this.lblComment.Visible = false;
            // 
            // textBoxComment
            // 
            this.textBoxComment.Location = new System.Drawing.Point(13, 182);
            this.textBoxComment.MaxLength = 999;
            this.textBoxComment.Name = "textBoxComment";
            this.textBoxComment.Size = new System.Drawing.Size(157, 20);
            this.textBoxComment.TabIndex = 29;
            this.textBoxComment.Visible = false;
            // 
            // lblLastCommentCaption
            // 
            this.lblLastCommentCaption.AutoSize = true;
            this.lblLastCommentCaption.Location = new System.Drawing.Point(9, 197);
            this.lblLastCommentCaption.Name = "lblLastCommentCaption";
            this.lblLastCommentCaption.Size = new System.Drawing.Size(134, 13);
            this.lblLastCommentCaption.TabIndex = 32;
            this.lblLastCommentCaption.Text = "Last comment for this card:";
            this.lblLastCommentCaption.Visible = false;
            // 
            // lblLastComment
            // 
            this.lblLastComment.Location = new System.Drawing.Point(78, 216);
            this.lblLastComment.Name = "lblLastComment";
            this.lblLastComment.Size = new System.Drawing.Size(143, 58);
            this.lblLastComment.TabIndex = 33;
            this.lblLastComment.Text = " ";
            // 
            // pnlCardDetected
            // 
            this.pnlCardDetected.Controls.Add(this.lblReadModiValueCaption);
            this.pnlCardDetected.Controls.Add(this.lblReadModiValue);
            this.pnlCardDetected.Controls.Add(this.lblRFIDCaption);
            this.pnlCardDetected.Controls.Add(this.lblRFID);
            this.pnlCardDetected.Controls.Add(this.lblLastComment);
            this.pnlCardDetected.Controls.Add(this.lblModeCaption);
            this.pnlCardDetected.Controls.Add(this.lblLastCommentCaption);
            this.pnlCardDetected.Controls.Add(this.lblMode);
            this.pnlCardDetected.Controls.Add(this.lblFolderCaption);
            this.pnlCardDetected.Controls.Add(this.lblFolder);
            this.pnlCardDetected.Controls.Add(this.lblStartPosCaption);
            this.pnlCardDetected.Controls.Add(this.lblStartPos);
            this.pnlCardDetected.Controls.Add(this.lblEndPosCaption);
            this.pnlCardDetected.Controls.Add(this.lblEndPos);
            this.pnlCardDetected.Location = new System.Drawing.Point(3, 81);
            this.pnlCardDetected.Name = "pnlCardDetected";
            this.pnlCardDetected.Size = new System.Drawing.Size(229, 289);
            this.pnlCardDetected.TabIndex = 36;
            // 
            // lblReadModiValueCaption
            // 
            this.lblReadModiValueCaption.Location = new System.Drawing.Point(3, 93);
            this.lblReadModiValueCaption.Name = "lblReadModiValueCaption";
            this.lblReadModiValueCaption.Size = new System.Drawing.Size(70, 13);
            this.lblReadModiValueCaption.TabIndex = 34;
            this.lblReadModiValueCaption.Text = "Value:";
            this.lblReadModiValueCaption.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblReadModiValue
            // 
            this.lblReadModiValue.AutoSize = true;
            this.lblReadModiValue.Location = new System.Drawing.Point(78, 93);
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
            this.pnlModiCardAction.Location = new System.Drawing.Point(435, 112);
            this.pnlModiCardAction.Name = "pnlModiCardAction";
            this.pnlModiCardAction.Size = new System.Drawing.Size(181, 258);
            this.pnlModiCardAction.TabIndex = 39;
            // 
            // pnlModeBehaviour
            // 
            this.pnlModeBehaviour.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlModeBehaviour.Controls.Add(this.comboBox_ModiBehaviour);
            this.pnlModeBehaviour.Location = new System.Drawing.Point(14, 110);
            this.pnlModeBehaviour.Name = "pnlModeBehaviour";
            this.pnlModeBehaviour.Size = new System.Drawing.Size(157, 23);
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
            this.comboBox_ModiBehaviour.Size = new System.Drawing.Size(155, 21);
            this.comboBox_ModiBehaviour.TabIndex = 16;
            // 
            // lblModeBehaviour
            // 
            this.lblModeBehaviour.Location = new System.Drawing.Point(12, 91);
            this.lblModeBehaviour.Name = "lblModeBehaviour";
            this.lblModeBehaviour.Size = new System.Drawing.Size(58, 13);
            this.lblModeBehaviour.TabIndex = 32;
            this.lblModeBehaviour.Text = "Behaviour:";
            this.lblModeBehaviour.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // lblMinutes
            // 
            this.lblMinutes.AutoSize = true;
            this.lblMinutes.Location = new System.Drawing.Point(142, 62);
            this.lblMinutes.Name = "lblMinutes";
            this.lblMinutes.Size = new System.Drawing.Size(23, 13);
            this.lblMinutes.TabIndex = 31;
            this.lblMinutes.Text = "min";
            // 
            // lblModiValue
            // 
            this.lblModiValue.Location = new System.Drawing.Point(18, 62);
            this.lblModiValue.Name = "lblModiValue";
            this.lblModiValue.Size = new System.Drawing.Size(59, 13);
            this.lblModiValue.TabIndex = 29;
            this.lblModiValue.Text = "Value:";
            this.lblModiValue.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // textBox_ModiValue
            // 
            this.textBox_ModiValue.Location = new System.Drawing.Point(82, 59);
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
            this.pnlModeCardOptions.Location = new System.Drawing.Point(13, 23);
            this.pnlModeCardOptions.Name = "pnlModeCardOptions";
            this.pnlModeCardOptions.Size = new System.Drawing.Size(158, 23);
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
            this.comboBox_ModiCardOptions.Size = new System.Drawing.Size(156, 21);
            this.comboBox_ModiCardOptions.TabIndex = 16;
            this.comboBox_ModiCardOptions.SelectedIndexChanged += new System.EventHandler(this.comboBox_ModiCardOptions_SelectedIndexChanged);
            // 
            // btnWriteModiCard
            // 
            this.btnWriteModiCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(128)))));
            this.btnWriteModiCard.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnWriteModiCard.Location = new System.Drawing.Point(14, 220);
            this.btnWriteModiCard.Name = "btnWriteModiCard";
            this.btnWriteModiCard.Size = new System.Drawing.Size(156, 23);
            this.btnWriteModiCard.TabIndex = 24;
            this.btnWriteModiCard.Text = "Write Modification Card";
            this.btnWriteModiCard.UseVisualStyleBackColor = false;
            this.btnWriteModiCard.Click += new System.EventHandler(this.btnWriteModiCard_Click);
            // 
            // pnlMusicCardAction
            // 
            this.pnlMusicCardAction.Controls.Add(this.checkExtendCard);
            this.pnlMusicCardAction.Controls.Add(this.lblFolderOnSource);
            this.pnlMusicCardAction.Controls.Add(this.textBoxComment);
            this.pnlMusicCardAction.Controls.Add(this.lblStartOnSource);
            this.pnlMusicCardAction.Controls.Add(this.textBoxFolderOnSD);
            this.pnlMusicCardAction.Controls.Add(this.lblComment);
            this.pnlMusicCardAction.Controls.Add(this.textBoxStartOnSD);
            this.pnlMusicCardAction.Controls.Add(this.lblEndOnSource);
            this.pnlMusicCardAction.Controls.Add(this.pnlModes);
            this.pnlMusicCardAction.Controls.Add(this.textBoxEndOnSD);
            this.pnlMusicCardAction.Controls.Add(this.btnBrowsMusic);
            this.pnlMusicCardAction.Controls.Add(this.btnWriteMusicCard);
            this.pnlMusicCardAction.Location = new System.Drawing.Point(238, 112);
            this.pnlMusicCardAction.Name = "pnlMusicCardAction";
            this.pnlMusicCardAction.Size = new System.Drawing.Size(181, 258);
            this.pnlMusicCardAction.TabIndex = 40;
            // 
            // radio_MusicCard
            // 
            this.radio_MusicCard.AutoSize = true;
            this.radio_MusicCard.Checked = true;
            this.radio_MusicCard.Location = new System.Drawing.Point(16, 3);
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
            this.radio_ModiCard.Location = new System.Drawing.Point(74, 3);
            this.radio_ModiCard.Name = "radio_ModiCard";
            this.radio_ModiCard.Size = new System.Drawing.Size(82, 17);
            this.radio_ModiCard.TabIndex = 42;
            this.radio_ModiCard.Text = "Modification";
            this.radio_ModiCard.UseVisualStyleBackColor = true;
            this.radio_ModiCard.CheckedChanged += new System.EventHandler(this.radio_Card_CheckedChanged);
            // 
            // pnlCardAction
            // 
            this.pnlCardAction.Controls.Add(this.radio_MusicCard);
            this.pnlCardAction.Controls.Add(this.radio_ModiCard);
            this.pnlCardAction.Location = new System.Drawing.Point(238, 81);
            this.pnlCardAction.Name = "pnlCardAction";
            this.pnlCardAction.Size = new System.Drawing.Size(181, 28);
            this.pnlCardAction.TabIndex = 43;
            // 
            // pnlSeparator
            // 
            this.pnlSeparator.BackColor = System.Drawing.SystemColors.ControlDark;
            this.pnlSeparator.Location = new System.Drawing.Point(234, 81);
            this.pnlSeparator.Name = "pnlSeparator";
            this.pnlSeparator.Size = new System.Drawing.Size(1, 289);
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
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(786, 597);
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
        private Tonuino_RFID_Creator.ExtendedComboBox comboBox_MusicCardModes;
        private System.Windows.Forms.Label lblFolderOnSource;
        private System.Windows.Forms.Label lblStartOnSource;
        private System.Windows.Forms.TextBox textBoxFolderOnSD;
        private System.Windows.Forms.TextBox textBoxStartOnSD;
        private System.Windows.Forms.TextBox textBoxEndOnSD;
        private System.Windows.Forms.Label lblEndOnSource;
        private System.Windows.Forms.Button btnBrowsMusic;
        private System.Windows.Forms.Button btnWriteMusicCard;
        private System.Windows.Forms.CheckBox checkExtendCard;
        private System.Windows.Forms.Panel pnlModes;
        private System.Windows.Forms.Label lblComment;
        private System.Windows.Forms.TextBox textBoxComment;
        private System.Windows.Forms.Label lblLastCommentCaption;
        private System.Windows.Forms.Label lblLastComment;
        private System.Windows.Forms.Panel pnlCardDetected;
        private System.Windows.Forms.Panel pnlModiCardAction;
        private System.Windows.Forms.Label lblMinutes;
        private System.Windows.Forms.Label lblModiValue;
        private System.Windows.Forms.TextBox textBox_ModiValue;
        private System.Windows.Forms.Panel pnlModeCardOptions;
        private Tonuino_RFID_Creator.ExtendedComboBox comboBox_ModiCardOptions;
        private System.Windows.Forms.Button btnWriteModiCard;
        private System.Windows.Forms.Panel pnlMusicCardAction;
        private System.Windows.Forms.RadioButton radio_MusicCard;
        private System.Windows.Forms.RadioButton radio_ModiCard;
        private System.Windows.Forms.Panel pnlCardAction;
        private System.Windows.Forms.Panel pnlSeparator;
        private System.Windows.Forms.Panel pnlPorts;
        private Tonuino_RFID_Creator.ExtendedComboBox comboBox_Ports;
        private System.Windows.Forms.Label lblPorts;
        private System.Windows.Forms.Label lblReadModiValueCaption;
        private System.Windows.Forms.Label lblReadModiValue;
        private System.Windows.Forms.Panel pnlModeBehaviour;
        private ExtendedComboBox comboBox_ModiBehaviour;
        private System.Windows.Forms.Label lblModeBehaviour;
    }
}

