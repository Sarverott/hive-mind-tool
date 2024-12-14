/*

import puppeteer from 'puppeteer';
import path from 'path';

const pathToExtension = path.join(process.cwd(), 'my-extension');
const browser = await puppeteer.launch({
  args: [
    `--disable-extensions-except=${pathToExtension}`,
    `--load-extension=${pathToExtension}`,
  ],
});

const workerTarget = await browser.waitForTarget(
  // Assumes that there is only one service worker created by the extension and its URL ends with background.js.
  target =>
    target.type() === 'service_worker' &&
    target.url().endsWith('background.js'),
);

const worker = await workerTarget.worker();

// Open a popup (available for Canary channels).
await worker.evaluate('chrome.action.openPopup();');

const popupTarget = await browser.waitForTarget(
  // Assumes that there is only one page with the URL ending with popup.html and that is the popup created by the extension.
  target => target.type() === 'page' && target.url().endsWith('popup.html'),
);

const popupPage = popupTarget.asPage();

// Test the popup page as you would any other page.

await browser.close();

*/

//               +

/* 
const browser = await puppeteer.connect({
  browserWSEndpoint: 'ws://127.0.0.1:9222/...',
});

const page = await browser.newPage();

browser.disconnect();
*/