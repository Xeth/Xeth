<div class="head">
    <div class="controls left">
        <div id="filterTransactionType" class="input" value="0">
            <select>
                <option value="all">All transactions</option>
                <option value="received">Received</option>
                <option value="sent">Sent</option>
            </select>
        </div>
        <div class="input date"><input type="text" id="filterTransactionTime" class="daterange" placeholder="date" /></div>
    </div>
    <div class="controls">
        <div id="filterTransactionAddress" ></div>
    </div>
</div>

<div class="scrollpage transactions">
    <div class="empty">no transactions to display</div>
    <div class="holder transactionList">
    </div>
</div>
<div class="transactions_total">
    <div class="total sent right">
        <span class="detail txtBalance">
            <span class="int"></span><span class="dec"></span>
        </span>
    </div>
    <div class="total received">
        <span class="detail txtBalance">
            <span class="int"></span><span class="dec"></span>
        </span>
    </div>
</div>
