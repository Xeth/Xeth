

<div class="head">
    <div class="controls left">
		<select id="filterTransactionType">
			<option value="All">All transactions</option>
			<option value="Received">Received</option>
			<option value="Sent">Sent</option>
			<option value="Mined">Mined</option>
		</select>
        <div class="input date"><input type="text" id="filterTransactionTime" class="daterange" readonly placeholder="date" /></div>
    </div>
    <div class="controls">
        <div id="filterTransactionAddress" ></div>
    </div>
</div>

<div class="transactions scrollpage">
    <div class="empty">no transactions to display</div>
    <div class="holder transactionList">
    </div>
</div>
<div class="transactions_total">
    <div class="total transactions hidden"></div>
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


