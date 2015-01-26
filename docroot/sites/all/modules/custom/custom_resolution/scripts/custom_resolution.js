(function ($) {
  var selectedParty;

  $(document).ready(function() {
    var fractions = $('.views-field-field-fraction');
    var partiesFilter = $('#edit-supported-parties-filter');
    selectedParty = partiesFilter.val();
    fractions.each(toggleRows);
    partiesFilter.change(filterDelegates);
  });

  function filterDelegates() {
    var fractions = $('.views-field-field-fraction');
    selectedParty = $(this).val();
    fractions.each(toggleRows);
  }

  function toggleRows() {
    var currentFraction = $(this).children('.field-content').text();
    var formItem = $(this).parents('.form-type-checkbox');

    if (currentFraction !== selectedParty) {
      formItem.hide();
    } else {
      formItem.show();
      console.log(true);
    }
  }

})(jQuery);