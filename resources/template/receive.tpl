<div class="formpage receive">
    <h1>To:<span class="controls"><a href="javascript:changePage('page_newAddress',0);">New address</a></span></h1>
    <div id="receiveTo" ></div>
    <div class="half_right controls">
        <div id="receiveQR" class="QR"></div>
        <div class="btns x2">
            <a href="javascript:void(0);" id="copyReceiveAddress" class="btn">Copy Address</a>
            <a href="javascript:void(0);" id="copyReceiveURI" class="btn highlight">Copy URI</a>
        </div>
    </div>
    <div class="half_left">
        <h1>Amount:</h1>
        <div class="input amount"><input id="receiveAmount" type="number" min="0" placeholder="0.00000000" /></div>
        <h1>Message:</h1>
        <textarea id="receiveMessage" name="" cols="" rows=""></textarea>
        <h1>URI:</h1>
        <textarea readonly class="txtURI" name="" cols="" rows=""></textarea>
    </div>
</div>
