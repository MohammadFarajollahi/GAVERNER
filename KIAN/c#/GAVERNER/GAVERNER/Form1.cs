using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;
using System.Text.Json;
namespace GAVERNER
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            updatePorts();
            CheckForIllegalCrossThreadCalls = false;
        }

        private void updatePorts()
        {
            // Retrieve the list of all COM ports on your Computer
            string[] ports = SerialPort.GetPortNames();
            foreach (string port in ports)
            {
                cmbPortName.Items.Add(port);
            }
        }
        private SerialPort ComPort = new SerialPort();
        int select;
        private void button1_Click(object sender, EventArgs e)
        {
            if (ComPort.IsOpen)
            {
                disconnect();
            }
            else
            {
                connect();
            }
        }

        private void disconnect()
        {
            ComPort.Close();
            btnConnect.Text = "Connect";
            //btnSend.Enabled = false;
            //groupBox1.Enabled = true;


        }

        private void connect()
        {
            bool error = false;
            ComPort.PortName = cmbPortName.Text;
            ComPort.BaudRate = int.Parse("115200");      //convert Text to Integer
            ComPort.Parity = (Parity)Enum.Parse(typeof(Parity), "None"); //convert Text to Parity
            ComPort.DataBits = int.Parse("8");        //convert Text to Integer
            ComPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), "1");  //convert Text to stop bits

            try  //always try to use this try and catch method to open your port. 
                 //if there is an error your program will not display a message instead of freezing.
            {
                //Open Port
                ComPort.Open();
                ComPort.DataReceived += SerialPortDataReceived;  //Check for received data. When there is data in the receive buffer,
                                                                 //it will raise this event, we need to subscribe to it to know when there is data
            }
            catch (UnauthorizedAccessException) { error = true; }
            catch (System.IO.IOException) { error = true; }
            catch (ArgumentException) { error = true; }

            if (error) MessageBox.Show(this, "Could not open the COM port. Most likely it is already in use, has been removed, or is unavailable.", "COM Port unavailable", MessageBoxButtons.OK, MessageBoxIcon.Stop);


            //if the port is open, Change the Connect button to disconnect, enable the send button.
            //and disable the groupBox to prevent changing configuration of an open port.
            if (ComPort.IsOpen)
            {
                btnConnect.Text = "Disconnect";
                // btnSend.Enabled = true;
            }
        }

        private void sendData()
        {
            ComPort.Write(txtSend.Text);

            // Show in the terminal window 
            rtxtDataArea.ForeColor = Color.Green;    //write sent text data in green colour              
            txtSend.Clear();                       //clear screen after sending data        
        }

        int temp;
        public class SensorData
        {
            public string maxrpm { get; set; }
            public string rpmtrl { get; set; }
            public string currentrpm { get; set; }
            public string checktime { get; set; }
            public string AngleUser { get; set; }
            public string minrpm { get; set; }
            public string sampletime { get; set; }

        }
        string id;
        string command;
        string message;
        private void SerialPortDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            try
            {
                var serialPort = (SerialPort)sender;
                String data = serialPort.ReadLine();
              //if(data.ToString().IndexOf("\r\n") >= 0)
                SetText(data);
            }
            catch (Exception ex)
            {
                rtxtDataArea.Text = "DATA receve error";
            }
        }

        delegate void SetTextCallback(string text);
        private void SetText(string text)
        {
            // text = "s1,34,129,87Bs2,24,19,97Bs3,24,19,97Bs4,24,19,97B\r\n";
            if (text != "" && text != null)
            {
                string s = text;
                //s += "\r\n";
                // 
                
                try
                {
                    SensorData sensor = JsonSerializer.Deserialize<SensorData>(s);
                    //id = sensor.id;
                    //command = sensor.command;
                    //message = sensor.message;
                     textBox1.Text = sensor.checktime;
                     textBox3.Text = sensor.AngleUser;
                    textBox6.Text = sensor.minrpm;
                    textBox2.Text = sensor.maxrpm;
                    textBox4.Text = sensor.rpmtrl;
                    textBox7.Text = sensor.sampletime;
                    textBox5.Text = sensor.currentrpm;
                    //
                }
                catch (Exception ex)
                {
                   // rtxtDataArea.Text += "jason DATA error\r\n";
                }
                    //*****Print to textbox****
                    if (this.rtxtDataArea.InvokeRequired &&  checkBox1.Checked)
                {
                    rtxtDataArea.ForeColor = Color.Black;    //write text data in Green colour

                    SetTextCallback d = new SetTextCallback(SetText);
                    this.Invoke(d, new object[] { text });
                }
                else
                {
                    if(checkBox1.Checked) this.rtxtDataArea.AppendText(text);
                }
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (ComPort.IsOpen)
            {
                disconnect();
            }
            else
            {
                connect();
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            updatePorts();
        }
    }
}
