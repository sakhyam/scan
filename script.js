function showResult(id, text) {
  document.getElementById(id).innerText = text;
}

function checkPassword() {
  const password = document.getElementById('passwordInput').value;
  let score = 0;

  if (password.length >= 8) score++;
  if (/[A-Z]/.test(password)) score++;
  if (/[a-z]/.test(password)) score++;
  if (/[0-9]/.test(password)) score++;
  if (/[^A-Za-z0-9]/.test(password)) score++;

  let strength = 'Very Weak';
  if (score === 5) strength = 'Very Strong';
  else if (score === 4) strength = 'Strong';
  else if (score === 3) strength = 'Moderate';
  else if (score === 2) strength = 'Weak';

  showResult('passwordResult', `Strength: ${strength}`);
}

async function generateHash() {
  const text = document.getElementById('hashInput').value;
  if (!text) {
    showResult('hashResult', 'Enter text to hash.');
    return;
  }

  const data = new TextEncoder().encode(text);
  const hashBuffer = await crypto.subtle.digest('SHA-256', data);
  const hashArray = Array.from(new Uint8Array(hashBuffer));
  const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
  showResult('hashResult', `SHA-256: ${hashHex}`);
}

function checkPort() {
  const port = parseInt(document.getElementById('portInput').value, 10);

  if (isNaN(port) || port < 1 || port > 65535) {
    showResult('portResult', 'Enter a valid port number between 1 and 65535.');
    return;
  }

  const commonPorts = {
    20: 'FTP Data',
    21: 'FTP Control',
    22: 'SSH',
    23: 'Telnet',
    25: 'SMTP',
    53: 'DNS',
    80: 'HTTP',
    110: 'POP3',
    143: 'IMAP',
    443: 'HTTPS'
  };

  showResult('portResult', commonPorts[port] ? `Common service: ${commonPorts[port]}` : 'Unknown / uncommon port');
}
